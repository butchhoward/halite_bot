#pragma once

#include "hlt/hlt.hpp"
#include "hlt/navigation.hpp"

#include "planet_info.hpp"
#include "routing.hpp"

namespace hlt {

    std::ostream& operator<<(std::ostream& out, const Entity& entity);
    std::ostream& operator<<(std::ostream& out, const Planet& planet);
    std::ostream& operator<<(std::ostream& out, const ShipDockingStatus& docking_status);
    std::ostream& operator<<(std::ostream& out, const Ship& ship);
    std::ostream& operator<<(std::ostream& out, const Map& map);
        
}

std::ostream& operator<<(std::ostream& out, const planet_info& p);
std::ostream& operator<<(std::ostream& out, const Routing& routing);


void log_all_planets(const std::vector<hlt::Planet>& planets);
