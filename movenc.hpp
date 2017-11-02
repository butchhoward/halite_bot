#pragma once

#include "hlt/move.hpp"
#include "hlt/types.hpp"

class MoveNC
{
  private:
    hlt::MoveType type;
    hlt::EntityId ship_id;
    int move_thrust;
    int move_angle_deg;
    hlt::EntityId dock_to;

  public:
    MoveNC();

    MoveNC(const MoveNC &rhs);

    MoveNC(const hlt::Move &rhs);

    MoveNC &operator=(const MoveNC &rhs);

    MoveNC &operator=(const hlt::Move &rhs);

    static const hlt::Move toMove(const MoveNC &m);
};
