#pragma once

#include "movenc.hpp"
#include "planet_info.hpp"

#include "hlt/map.hpp"
#include "hlt/types.hpp"
#include "hlt/ship.hpp"
#include "hlt/planet.hpp"

#include <unordered_set>


class Routing
{
public:
    Routing();

    planet_info add_planet(const hlt::Planet &planet);
    void add_ship_to_planet(const hlt::Planet& planet, const hlt::Ship& ship);
    int planet_ship_count(const hlt::Planet& planet);
    const hlt::possibly<MoveNC> route_a_ship(const hlt::Ship& ship);
    void clear();    

    void set_map(const hlt::Map& the_map);
    void set_player_id(const hlt::EntityId& the_player_id);

private:
    hlt::possibly<MoveNC> attack_planet(const hlt::Ship &ship, const hlt::Planet &planet);
    hlt::possibly<MoveNC> attack_something(const hlt::Ship &ship);
    hlt::possibly<MoveNC> dock_at_planet(const hlt::Ship &ship, const hlt::Planet &planet);
    void update_routes_from_turn_map();
    hlt::possibly<const hlt::EntityId> ship_en_route_to_any_planet(const hlt::Ship& ship) const;
    void remove_ship_from_planet(const hlt::EntityId &planet_id, const hlt::EntityId &ship_id);
    hlt::possibly<MoveNC> continue_ships_previously_routed(const hlt::Ship& ship);    
    void add_current_planets();
    void remove_destroyed_ships();
    void remove_destroyed_planets();
    
    hlt::EntityId player_id;
    hlt::Map map;
    hlt::entity_map<planet_info> planets;

    friend std::ostream& operator<<(std::ostream& out, const Routing& routing);
};

void log_routing();
