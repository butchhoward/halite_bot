#pragma once

#include "hlt/hlt.hpp"
#include "hlt/navigation.hpp"

namespace hlt {

    std::ostream& operator<<(std::ostream& out, const Entity& entity);
    std::ostream& operator<<(std::ostream& out, const Planet& planet);
    std::ostream& operator<<(std::ostream& out, const ShipDockingStatus& docking_status);
    std::ostream& operator<<(std::ostream& out, const Ship& ship);
}

void log_all_planets(const std::vector<hlt::Planet>& planets);
