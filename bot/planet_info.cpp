#include "planet_info.hpp"

PlanetInfo::PlanetInfo(const hlt::Planet &planet)
{
    add_planet(planet);
}

void PlanetInfo::add_planet(const hlt::Planet &planet)
{
    add_target(planet.entity_id);

    for (const hlt::EntityId &ship_id : planet.docked_ships)
    {
        ships_en_route.erase(ship_id);
    }
}

TargetInfo::TargetInfo()
    : target_id(-1)
{
}

void TargetInfo::add_target(const hlt::EntityId &targetid)
{
    target_id = targetid;
}

void TargetInfo::add_ship(const hlt::Ship &ship)
{
    ships_en_route.insert(ship.entity_id);
}

void TargetInfo::revoke_ship_en_route(const hlt::EntityId &ship_id)
{
    ships_en_route.erase(ship_id);
}

int TargetInfo::ship_count() const
{
    return ships_en_route.size();
}

bool TargetInfo::ship_en_route(const hlt::Ship &ship) const
{
    return ships_en_route.find(ship.entity_id) != ships_en_route.end();
}

std::unordered_set<hlt::EntityId> TargetInfo::all_ships() const
{
    std::unordered_set<hlt::EntityId> the_ships;
    the_ships.insert(ships_en_route.begin(), ships_en_route.end());
    return the_ships;
}
