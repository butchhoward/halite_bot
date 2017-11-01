#include "planet_info.hpp"

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
