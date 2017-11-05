#pragma once

#include "../hlt/types.hpp"
#include "../hlt/planet.hpp"
#include "../hlt/ship.hpp"

#include <unordered_set>

class TargetInfo 
{
public:
    TargetInfo();
    
    void add_target(const hlt::EntityId& targetid);
    void add_ship(const hlt::Ship &ship);
    void revoke_ship_en_route(const hlt::EntityId &ship_id);
    int ship_count() const;
    bool ship_en_route(const hlt::Ship& ship) const;
    std::unordered_set<hlt::EntityId> all_ships() const;

protected:
    hlt::EntityId target_id;
    std::unordered_set<hlt::EntityId> ships_en_route;

    friend std::ostream& operator<<(std::ostream& out, const TargetInfo& p);
    
};

class PlanetInfo : public TargetInfo
{
public:
    PlanetInfo()
    {
    }

    PlanetInfo(const hlt::Planet &planet);
    
    void add_planet(const hlt::Planet& planet);

private:

    friend std::ostream& operator<<(std::ostream& out, const PlanetInfo& p);
    
};
