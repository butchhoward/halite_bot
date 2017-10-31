#include "planet_ship_info.hpp"
#include "hlt/navigation.hpp"
#include "bot_utils.hpp"


planet_ship_info::planet_ship_info()
{    
}
void planet_ship_info::clear()
{
    planets.clear();
}

void planet_ship_info::add_ship_to_planet(const hlt::EntityId& planet_id, const hlt::EntityId& ship_id)
{
    auto it = planets.find(planet_id);
    if (it == planets.end())
    {
        planet_info info;
        info.planet_id = planet_id;
        info.ships.insert(ship_id);
        planets[planet_id] = info;
    }
    else
    {
        planet_info info = it->second;
        info.ships.insert(ship_id);
        planets[planet_id] = info;
    }
}

int planet_ship_info::planet_ship_count(const hlt::EntityId& planet_id)
{
    auto it = planets.find(planet_id);
    if (it != planets.end())
    {
        planet_info info = it->second;
        return info.ships.size();
    }

    return 0;
}

const hlt::possibly<MoveNC> planet_ship_info::find_a_planet(const hlt::Map& map, const hlt::Ship& ship, const hlt::EntityId& player_id)
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
            if (planet_less_than_halffull(planet))
            {
                hlt::Log::out() << "\t\thalf full ships: " << planet.docked_ships.size() << " spots: " << planet.docking_spots << std::endl;
                if (ship.can_dock(planet))
                {
                    hlt::Log::out() << "\t\thalf full docking:" << planet.entity_id << std::endl;
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

            if (planet_ship_count(planet.entity_id) > 0)
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
        add_ship_to_planet(planet_id, ship.entity_id);
    }

    return move;
}
