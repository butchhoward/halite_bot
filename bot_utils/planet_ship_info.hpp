
#include <unordered_set>

#include "hlt/map.hpp"
#include "hlt/types.hpp"
#include "hlt/ship.hpp"
#include "hlt/planet.hpp"
#include "hlt/log.hpp"
#include "bot_utils/movenc.hpp"


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


class planet_ship_info
{
public:
    planet_ship_info();
    planet_info add_planet(const hlt::Planet &planet);
    void add_ship_to_planet(const hlt::Planet& planet, const hlt::EntityId& ship);
    int planet_ship_count(const hlt::Planet& planet);
    const hlt::possibly<MoveNC> find_a_planet(const hlt::Map& map, const hlt::Ship& ship, const hlt::EntityId& player_id);
    void clear();    

private:
    hlt::entity_map<planet_info> planets;
};