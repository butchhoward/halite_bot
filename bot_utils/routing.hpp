
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
    void add_ship_to_planet(const hlt::Planet& planet, const hlt::EntityId& ship);
    int planet_ship_count(const hlt::Planet& planet);
    const hlt::possibly<MoveNC> find_a_planet(const hlt::Map& map, const hlt::Ship& ship, const hlt::EntityId& player_id);
    void clear();    

    void set_map(const hlt::Map& the_map);
    void set_player_id(const hlt::EntityId& the_player_id);
private:
    hlt::EntityId player_id;
    hlt::Map map;
    hlt::entity_map<planet_info> planets;
};