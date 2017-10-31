#pragma once

#include "hlt/hlt.hpp"

bool planet_less_than_halffull(const hlt::Planet &planet);
hlt::possibly<hlt::Move> attack_something(const hlt::Map map, const hlt::Planet &planet, const hlt::Ship &ship);
