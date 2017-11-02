#include "routing.hpp"

#include "hlt/navigation.hpp"
#include "hlt/log.hpp"

#include "bot_utils.hpp"
#include "log_utils.hpp"

#include <algorithm>

/////////////////
Routing::Routing()
    : player_id(-1),
      map(0, 0)
{
}

void Routing::set_player_id(const hlt::EntityId &the_player_id)
{
    player_id = the_player_id;
}

void Routing::set_map(const hlt::Map &the_map)
{
    //because map.hpp does not have adequate constructors or settors
    map.map_width = the_map.map_width;
    map.map_height = the_map.map_height;
    map.ships = the_map.ships;
    map.ship_map = the_map.ship_map;
    map.planets = the_map.planets;
    map.planet_map = the_map.planet_map;

    update_routes_from_turn_map();
}

void Routing::clear()
{
    planets.clear();
}

void Routing::update_routes_from_turn_map()
{
    remove_destroyed_ships();
    remove_docked_ships();
    remove_destroyed_planets();
    add_current_planets();
}

void Routing::add_current_planets()
{
    for (const auto &p : map.planets)
    {
        if (p.owner_id == player_id)
        {
            add_planet(p);
        }
    }
}

void Routing::remove_destroyed_ships()
{
    const std::vector<hlt::Ship> &player_ships = map.ships.at(player_id);

    for (const auto &p : planets)
    {
        for (const auto &s : p.second.all_ships())
        {
            if (std::find_if(player_ships.begin(),
                             player_ships.end(),
                             [s](const hlt::Ship &ps) { return ps.entity_id == s; }) == player_ships.end())
            {

                hlt::Log::out() << "remove_destroyed_ships p.first= " << p.first << " s= " << s << std::endl;
                remove_ship_from_planet(p.first, s);
            }
        }
    }
}

void Routing::remove_docked_ships()
{
    const std::vector<hlt::Ship> &player_ships = map.ships.at(player_id);

    for (const auto &s : player_ships)
    {
        if (s.docking_status == hlt::ShipDockingStatus::Docked)
        {
            for ( const auto& p : planets )
            {
                if (ship_en_route_to_any_planet(s).second)
                {
                    hlt::Log::out() << "remove_docked_ships from planet= " << p.first << " s= " << s.entity_id << std::endl;
                    remove_ship_from_planet(p.first, s.entity_id);
                }
            }
        }
    }
}

void Routing::remove_destroyed_planets()
{
}

PlanetInfo Routing::add_planet(const hlt::Planet &planet)
{
    PlanetInfo p;
    auto it = planets.find(planet.entity_id);
    if (it == planets.end())
    {
        p.add_planet(planet);
        planets[planet.entity_id] = p;
    }
    else
    {
        p = it->second;
    }

    return p;
}

void Routing::add_ship_to_planet(const hlt::Planet &planet, const hlt::Ship &ship)
{
    PlanetInfo info;
    auto it = planets.find(planet.entity_id);
    if (it == planets.end())
    {
        info = add_planet(planet);
    }
    else
    {
        info = it->second;
    }
    info.add_ship_en_route(ship);
    planets[planet.entity_id] = info;
}

void Routing::remove_ship_from_planet(const hlt::EntityId &planet_id, const hlt::EntityId &ship_id)
{
    PlanetInfo info;
    auto it = planets.find(planet_id);
    if (it != planets.end())
    {
        info = it->second;
        info.revoke_ship_en_route(ship_id);
        planets[planet_id] = info;
    }
}

int Routing::planet_ship_count(const hlt::Planet &planet)
{
    auto it = planets.find(planet.entity_id);
    if (it != planets.end())
    {
        PlanetInfo info = it->second;
        return info.en_route_count();
    }

    return 0;
}

hlt::possibly<const hlt::EntityId> Routing::ship_en_route_to_any_planet(const hlt::Ship &ship) const
{
    for (const auto &p : planets)
    {
        if (p.second.ship_en_route(ship))
        {
            return std::make_pair(p.first, true);
        }
    }
    return std::make_pair(-1, false);
}

const hlt::possibly<MoveNC> Routing::route_a_ship(const hlt::Ship &ship)
{
    hlt::possibly<MoveNC> move(hlt::Move::noop(), false);

    move = continue_ships_previously_routed(ship);
    if (move.second)
    {
        return move;
    }

    for (const hlt::Planet &planet : map.planets)
    {
        hlt::Log::out() << "Checking Planet " << planet << std::endl;

        if (planet_ship_count(planet) > 0)
        {
            hlt::Log::out() << "a ship is already en route to this planet" << planet.entity_id << std::endl;
            continue;
        }

        if (!planet.owned || planet.owner_id == player_id)
        {
            hlt::Log::out() << "\tPossible planet: " << planet.entity_id << " ships en route: " << planet_ship_count(planet) << std::endl;

            if (planet_ship_count(planet) == 0)
            {
                hlt::Log::out() << "\tplanet with no ships this turn: " << std::endl;
                move = dock_at_planet(ship, planet);
                if (move.second)
                {
                    add_ship_to_planet(planet, ship);
                    break;
                }
            }

            if (!planet.is_full())
            {
                hlt::Log::out() << "\t\tunfull ships: " << planet.docked_ships.size() << " spots: " << planet.docking_spots << std::endl;
                move = dock_at_planet(ship, planet);
                if (move.second)
                {
                    add_ship_to_planet(planet, ship);
                    break;
                }
            }
        }
    }

    if (!move.second)
    {
        move = attack_something(ship);
    }

    return move;
}


hlt::possibly<MoveNC> Routing::continue_ships_previously_routed(const hlt::Ship& ship)
{
    hlt::possibly<MoveNC> move(hlt::Move::noop(), false);
    if (ship.docking_status == hlt::ShipDockingStatus::Docked)
    {
        hlt::Log::out() << "ship already docked:" << ship.entity_id << std::endl;
        move = std::make_pair(MoveNC(hlt::Move::noop()), true);
        return move;
    }   

    auto enroute = ship_en_route_to_any_planet(ship);

    if (enroute.second)
    {
        hlt::Log::out() << "ship " << ship.entity_id << " already has route to planet " << enroute.first << std::endl;
        const hlt::Planet &planet = map.get_planet(enroute.first);

        if (ship.docking_status != hlt::ShipDockingStatus::Undocked)
        {
            hlt::Log::out() << "ship already docked:" << ship.entity_id << std::endl;
            remove_ship_from_planet(planet.entity_id, ship.entity_id);
        }   
        else if (!planet.owned || planet.owner_id == player_id)
        {
            move = dock_at_planet(ship, planet);
        }
        else
        {
            //other player got there first, let the routing below re-direct the ship
            //bah: side affects
            remove_ship_from_planet(planet.entity_id, ship.entity_id);
        }
    }
    
    return move;
}

hlt::possibly<MoveNC> Routing::attack_something(const hlt::Ship &ship)
{
    hlt::Log::out() << "---attack something with : " << ship.entity_id << std::endl;

    hlt::possibly<MoveNC> move(hlt::Move::noop(), false);

    for (const auto &planet : map.planets)
    {
        hlt::Log::out() << "\tmaybe attack planet: " << planet.entity_id << std::endl;

        if (planet.owned && planet.owner_id != player_id)
        {
            hlt::Log::out() << "\t\tattacking planet: " << planet.entity_id << std::endl;
            move = attack_planet(ship, planet);
            if (move.second)
            {
                add_ship_to_planet(planet, ship);
            }
            break;
        }
    }

    return move;
}

hlt::possibly<MoveNC> Routing::attack_planet(const hlt::Ship &ship, const hlt::Planet &planet)
{
    const int max_corrections = hlt::constants::MAX_NAVIGATION_CORRECTIONS / 4;
    const bool avoid_obstacles = true;
    const double angular_step_rad = M_PI / 180.0;
    const hlt::Location &target = ship.location.get_closest_point(planet.location, planet.radius / 2);

    hlt::possibly<hlt::Move> move = hlt::navigation::navigate_ship_towards_target(
        map,
        ship,
        target,
        hlt::constants::MAX_SPEED,
        avoid_obstacles,
        max_corrections,
        angular_step_rad);

    return std::make_pair(MoveNC(move.first), move.second);
}

hlt::possibly<MoveNC> Routing::dock_at_planet(const hlt::Ship &ship, const hlt::Planet &planet)
{
    hlt::possibly<MoveNC> move(hlt::Move::noop(), false);

    if (ship.can_dock(planet))
    {
        hlt::Log::out() << "\t\tdock at planet: " << planet.entity_id << std::endl;
        move = std::make_pair(hlt::Move::dock(ship.entity_id, planet.entity_id), true);
    }
    else
    {
        hlt::Log::out() << "\t\tnavigate toward dock at planet: " << planet.entity_id << std::endl;
        move = hlt::navigation::navigate_ship_to_dock(map, ship, planet, hlt::constants::MAX_SPEED / 2);
    }

    return move;
}