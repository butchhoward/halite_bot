#pragma once

#include "hlt/types.hpp"
#include "hlt/planet.hpp"

#include <unordered_set>

class planet_info 
{
public:
    planet_info();
    planet_info(const hlt::Planet& planet);

    void add_planet(const hlt::Planet& planet);
    void add_ship(const hlt::EntityId &ship);
    int ship_count();

private:
    hlt::EntityId planet_id;
    std::unordered_set<hlt::EntityId> ships;
};
