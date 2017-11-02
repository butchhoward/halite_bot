#include "bot_utils.hpp"
#include "log_utils.hpp"

bool planet_less_than_halffull(const hlt::Planet &planet)
{
    return planet.docked_ships.size() < (planet.docking_spots / 2);
}

