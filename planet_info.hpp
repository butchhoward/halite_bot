#pragma once

#include "hlt/types.hpp"
#include "hlt/planet.hpp"
#include "hlt/ship.hpp"

#include <unordered_set>

class PlanetInfo 
{
public:
    PlanetInfo();
    PlanetInfo(const hlt::Planet& planet);

    void add_planet(const hlt::Planet& planet);
    void add_ship(const hlt::Ship &ship);
    void add_ship_en_route(const hlt::Ship &ship);
    void revoke_ship_en_route(const hlt::EntityId &ship_id);
    int ship_count() const;
    int en_route_count() const;
    bool ship_en_route(const hlt::Ship& ship) const;
    std::unordered_set<hlt::EntityId> all_ships() const;

private:
    hlt::EntityId planet_id;
    std::unordered_set<hlt::EntityId> ships;
    std::unordered_set<hlt::EntityId> ships_en_route;

    friend std::ostream& operator<<(std::ostream& out, const PlanetInfo& p);
    
};
