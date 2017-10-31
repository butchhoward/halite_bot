#pragma once

#include "types.hpp"
#include "util.hpp"

namespace hlt {
    enum class MoveType {
        Noop = 0,
        Thrust,
        Dock,
        Undock,
    };

    struct Move {
        const MoveType type;
        const EntityId ship_id;
        const int move_thrust;
        const int move_angle_deg;
        const EntityId dock_to;

        static Move noop() {
            return { MoveType::Noop, 0, -1, -1, 0 };
        }

        static Move dock(EntityId ship_id, EntityId dock_to) {
            return { MoveType::Dock, ship_id, -1, -1, dock_to };
        }

        static Move undock(const EntityId ship_id) {
            return { MoveType::Undock, ship_id, -1, -1, 0 };
        }

        static Move thrust(const EntityId ship_id, const int thrust, const int angle_deg) {
            return { MoveType::Thrust, ship_id, thrust, angle_deg, 0 };
        }

        static Move thrust_rad(const EntityId ship_id, const int thrust, const double angle_rad) {
            return { MoveType::Thrust, ship_id, thrust, util::angle_rad_to_deg_clipped(angle_rad), 0 };
        }
    };

    class MoveNC {
    private:
        MoveType type;
        EntityId ship_id;
        int move_thrust;
        int move_angle_deg;
        EntityId dock_to;
    public:

        MoveNC():
            type(MoveType::Noop),
            ship_id(0),
            move_thrust(-1),
            move_angle_deg(-1),
            dock_to(0)                
        {
        }

        MoveNC(const MoveNC& rhs) :
            type(rhs.type),
            ship_id(rhs.ship_id),
            move_thrust(rhs.move_thrust),
            move_angle_deg(rhs.move_angle_deg),
            dock_to(rhs.dock_to)
        {
        }

        MoveNC(const Move& rhs) :
            type(rhs.type),
            ship_id(rhs.ship_id),
            move_thrust(rhs.move_thrust),
            move_angle_deg(rhs.move_angle_deg),
            dock_to(rhs.dock_to)
        {
        }

        MoveNC& operator=(const MoveNC& rhs)
        {
            type = rhs.type;
            ship_id = rhs.ship_id;
            move_thrust = rhs.move_thrust;
            move_angle_deg = rhs.move_angle_deg;
            dock_to = rhs.dock_to;
            return *this;
        }

        MoveNC& operator=(const Move& rhs)
        {
            type = rhs.type;
            ship_id = rhs.ship_id;
            move_thrust = rhs.move_thrust;
            move_angle_deg = rhs.move_angle_deg;
            dock_to = rhs.dock_to;
            return *this;
        }

        static const Move toMove(const MoveNC& m)
        {
            return Move{
                m.type,
                m.ship_id,
                m.move_thrust,
                m.move_angle_deg,
                m.dock_to
            };
        }
    
    };

}
