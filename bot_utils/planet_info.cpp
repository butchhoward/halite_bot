#include "planet_info.hpp"

PlanetInfo::PlanetInfo()
    : planet_id(-1)
{
}

PlanetInfo::PlanetInfo(const hlt::Planet &planet)
{
    add_planet(planet);
}

void PlanetInfo::add_planet(const hlt::Planet &planet)
{
    planet_id = planet.entity_id;
    for (const hlt::EntityId &ship_id : planet.docked_ships)
    {
        ships.insert(ship_id);
        ships_en_route.erase(ship_id);
    }
}

void PlanetInfo::add_ship(const hlt::Ship &ship)
{
    ships.insert(ship.entity_id);
}

void PlanetInfo::add_ship_en_route(const hlt::Ship &ship)
{
    ships_en_route.insert(ship.entity_id);
}

void PlanetInfo::revoke_ship_en_route(const hlt::EntityId &ship_id)
{
    ships_en_route.erase(ship_id);
}

int PlanetInfo::ship_count() const
{
    return ships.size() + ships_en_route.size();
}

int PlanetInfo::en_route_count() const
{
    return ships_en_route.size();
}

bool PlanetInfo::ship_en_route(const hlt::Ship& ship) const
{
    return ships_en_route.find(ship.entity_id) != ships_en_route.end();
}

std::unordered_set<hlt::EntityId> PlanetInfo::all_ships() const
{
    std::unordered_set<hlt::EntityId> the_ships;
    the_ships.insert(ships.begin(), ships.end());
    the_ships.insert(ships_en_route.begin(), ships_en_route.end());
    return the_ships;
}
