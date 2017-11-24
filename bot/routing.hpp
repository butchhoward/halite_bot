#pragma once

#include "movenc.hpp"
#include "planet_info.hpp"

#include "../hlt/map.hpp"
#include "../hlt/types.hpp"
#include "../hlt/ship.hpp"
#include "../hlt/planet.hpp"

#include <unordered_set>

using PlanetId = hlt::EntityId;
using ShipId = hlt::EntityId;
using PLANET_MAYBE = hlt::possibly<const hlt::EntityId>;
using MOVE_MAYBE = hlt::possibly<MoveNC>;
using PLANET_MOVE_MAYBE = std::pair<PlanetId, MOVE_MAYBE>;
using SHIP_MOVE_MAYBE = std::pair<ShipId, MOVE_MAYBE>;

class Routing
{
public:
    Routing();

    PlanetInfo add_planet(const hlt::Planet &planet);
    void add_ship_to_planet(const hlt::Planet& planet, const hlt::Ship& ship);
    int planet_ship_count(const hlt::Planet& planet);
    const MOVE_MAYBE route_a_ship(const hlt::Ship& ship);
    void clear();    

    void set_map(const hlt::Map& the_map);
    void set_player_id(const hlt::EntityId& the_player_id);

private:
    MOVE_MAYBE attack_entity(const hlt::Ship &ship, const hlt::Entity &thing);
    MOVE_MAYBE attack_something(const hlt::Ship &ship);
    PLANET_MOVE_MAYBE attack_some_planet(const hlt::Ship &ship);
    SHIP_MOVE_MAYBE attack_some_ship(const hlt::Ship &ship);
    MOVE_MAYBE dock_at_planet(const hlt::Ship &ship, const hlt::Planet &planet);
    void update_routes_from_turn_map();
    PLANET_MAYBE ship_en_route_to_any_planet(const hlt::Ship& ship) const;
    void remove_ship_from_planet(const hlt::EntityId &planet_id, const hlt::EntityId &ship_id);
    MOVE_MAYBE continue_ships_previously_routed(const hlt::Ship& ship);    
    void add_current_planets();
    void remove_destroyed_ships();
    void remove_destroyed_planets();
    void remove_docked_ships();
    
    
    hlt::EntityId player_id;
    hlt::Map map;
    hlt::entity_map<PlanetInfo> planets;

    friend std::ostream& operator<<(std::ostream& out, const Routing& routing);
};

void log_routing();
