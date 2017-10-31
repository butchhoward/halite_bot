#include "log_utils.hpp"

namespace hlt {

    std::ostream& operator<<(std::ostream& out, const Entity& entity) {
        out << " id: " << entity.entity_id
            << " owner_id: " << entity.owner_id
            << " Location: " << entity.location
            << " health: " << entity.health
            << " radius: " << entity.radius
        ;
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const Planet& planet) {
        out << "Planet: " << (const Entity&)planet
            << " owned: " << planet.owned
            << " remaining prod: " << planet.remaining_production
            << " current prod: " << planet.current_production
            << " spots: " << planet.docking_spots
            << " ships: " << planet.docked_ships.size()    
        ;
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const ShipDockingStatus& docking_status) {
        switch (docking_status)
        {
            case ShipDockingStatus::Undocked:  out << " Undocked "; break;
            case ShipDockingStatus::Docking:   out << " Docking "; break;
            case ShipDockingStatus::Docked:    out << " Docked "; break;
            case ShipDockingStatus::Undocking: out << " Undocking "; break;
        };
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const Ship& ship) {
        out << "Ship: " << (const Entity&)ship
            << " weapon_cooldown: " << ship.weapon_cooldown
            << " docking_status: " << ship.docking_status
            << " docking_progress: " << ship.docking_progress
            << " docked_planet id: " << ship.docked_planet
        ;
        return out;
    }
}

void log_all_planets(const std::vector<hlt::Planet>& planets)
{
    for (const hlt::Planet &planet : planets)
    {
        hlt::Log::out() << planet << std::endl;
    }
}
