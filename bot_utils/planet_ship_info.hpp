
#include <unordered_set>

#include "hlt/map.hpp"
#include "hlt/types.hpp"
#include "hlt/ship.hpp"
#include "hlt/planet.hpp"
#include "hlt/log.hpp"
#include "bot_utils/movenc.hpp"


typedef struct planet_info 
{
    hlt::EntityId planet_id;
    std::unordered_set<hlt::EntityId> ships;
} planet_info;


class planet_ship_info
{
public:
    planet_ship_info();
    void add_ship_to_planet(const hlt::EntityId& planet_id, const hlt::EntityId& ship_id);
    int planet_ship_count(const hlt::EntityId& planet_id);
    const hlt::possibly<MoveNC> find_a_planet(const hlt::Map& map, const hlt::Ship& ship, const hlt::EntityId& player_id);
    void clear();    

private:
    hlt::entity_map<planet_info> planets;
};