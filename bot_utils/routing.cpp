#include "routing.hpp"
#include "hlt/navigation.hpp"
#include "bot_utils.hpp"

planet_info::planet_info()
    : planet_id(-1)
{
}

planet_info::planet_info(const hlt::Planet &planet)
{
    add_planet(planet);
}

void planet_info::add_planet(const hlt::Planet &planet)
{
    planet_id = planet.entity_id;
    for (const hlt::EntityId &ship : planet.docked_ships)
    {
        add_ship(ship);
    }
}

void planet_info::add_ship(const hlt::EntityId &ship)
{
    ships.insert(ship);
}

int planet_info::ship_count()
{
    return ships.size();
}

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
}

void Routing::clear()
{
    planets.clear();
}

planet_info Routing::add_planet(const hlt::Planet &planet)
{
    planet_info p(planet);
    planets[planet.entity_id] = p;
    return p;
}

void Routing::add_ship_to_planet(const hlt::Planet &planet, const hlt::EntityId &ship)
{
    planet_info info;
    auto it = planets.find(planet.entity_id);
    if (it == planets.end())
    {
        info = add_planet(planet);
    }
    else
    {
        planet_info info = it->second;
    }
    info.add_ship(ship);
    planets[planet.entity_id] = info;
}

int Routing::planet_ship_count(const hlt::Planet &planet)
{
    auto it = planets.find(planet.entity_id);
    if (it != planets.end())
    {
        planet_info info = it->second;
        return info.ship_count();
    }

    return 0;
}

const hlt::possibly<MoveNC> Routing::find_a_planet(const hlt::Map &map, const hlt::Ship &ship, const hlt::EntityId &player_id)
{
    hlt::possibly<MoveNC> move(hlt::Move::noop(), false);
    hlt::EntityId planet_id(0); //todo: bah not in this function

    for (const hlt::Planet &planet : map.planets)
    {
        planet_id = planet.entity_id;

        hlt::Log::out() << "----planet: " << planet.entity_id << std::endl;
        //planet already occupied, just ignore it for now
        if (!planet.owned || planet.owner_id == player_id)
        {
            hlt::Log::out() << "\tPossible planet: " << planet.entity_id << std::endl;

            //Prefer planets that need workers. Dock if there, else go there
            if (!planet.is_full())
            {
                hlt::Log::out() << "\t\tunfull ships: " << planet.docked_ships.size() << " spots: " << planet.docking_spots << std::endl;
                if (ship.can_dock(planet))
                {
                    hlt::Log::out() << "\t\tunfull docking:" << planet.entity_id << std::endl;
                    move = std::make_pair(hlt::Move::dock(ship.entity_id, planet.entity_id), true);
                    break;
                }
                else
                {
                    move = hlt::navigation::navigate_ship_to_dock(map, ship, planet, hlt::constants::MAX_SPEED / 2);
                    if (move.second)
                    {
                        hlt::Log::out() << "\t\thalf full nav to dock: " << planet.entity_id << std::endl;
                        break;
                    }
                }
            }

            if (planet_ship_count(planet) > 0)
            {
                hlt::Log::out() << "\tplanet with no ships this turn: " << planet.entity_id << std::endl;
                move = hlt::navigation::navigate_ship_to_dock(map, ship, planet, hlt::constants::MAX_SPEED / 2);
                if (move.second)
                {
                    hlt::Log::out() << "\t\t\tdocking" << planet.entity_id << std::endl;
                    break;
                }
            }

            //Planet is not full and ship is close enough to dock: dock
            if (!planet.is_full() && ship.can_dock(planet))
            {
                hlt::Log::out() << "\tunfull docking: " << planet.entity_id << std::endl;
                move = std::make_pair(hlt::Move::dock(ship.entity_id, planet.entity_id), true);
                break;
            }
        }
    }

    //todo: don't do this in this function
    if (move.second)
    {
        //add_ship_to_planet(planet_id, ship.entity_id);
    }

    return move;
}
