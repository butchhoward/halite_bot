#include "bot_utils.hpp"
#include "log_utils.hpp"

bool planet_less_than_halffull(const hlt::Planet &planet)
{
    return planet.docked_ships.size() < (planet.docking_spots / 2);
}

hlt::possibly<hlt::Move> attack_something(const hlt::Map map, const hlt::Planet &planet, const hlt::Ship &ship)
{
    const int max_corrections = hlt::constants::MAX_NAVIGATION_CORRECTIONS / 4;
    const bool avoid_obstacles = true;
    const double angular_step_rad = M_PI / 180.0;
    const hlt::Location &target = ship.location.get_closest_point(planet.location, planet.radius / 2);

    return hlt::navigation::navigate_ship_towards_target(
        map,
        ship,
        target,
        hlt::constants::MAX_SPEED,
        avoid_obstacles,
        max_corrections,
        angular_step_rad);
}
