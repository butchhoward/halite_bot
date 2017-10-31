#include "movenc.hpp"

MoveNC::MoveNC() : type(hlt::MoveType::Noop),
                   ship_id(0),
                   move_thrust(-1),
                   move_angle_deg(-1),
                   dock_to(0)
{
}

MoveNC::MoveNC(const MoveNC &rhs) : type(rhs.type),
                                    ship_id(rhs.ship_id),
                                    move_thrust(rhs.move_thrust),
                                    move_angle_deg(rhs.move_angle_deg),
                                    dock_to(rhs.dock_to)
{
}

MoveNC::MoveNC(const hlt::Move &rhs) : type(rhs.type),
                                  ship_id(rhs.ship_id),
                                  move_thrust(rhs.move_thrust),
                                  move_angle_deg(rhs.move_angle_deg),
                                  dock_to(rhs.dock_to)
{
}

MoveNC &MoveNC::operator=(const MoveNC &rhs)
{
    type = rhs.type;
    ship_id = rhs.ship_id;
    move_thrust = rhs.move_thrust;
    move_angle_deg = rhs.move_angle_deg;
    dock_to = rhs.dock_to;
    return *this;
}

MoveNC &MoveNC::operator=(const hlt::Move &rhs)
{
    type = rhs.type;
    ship_id = rhs.ship_id;
    move_thrust = rhs.move_thrust;
    move_angle_deg = rhs.move_angle_deg;
    dock_to = rhs.dock_to;
    return *this;
}

const hlt::Move MoveNC::toMove(const MoveNC &m)
{
    return hlt::Move{
        m.type,
        m.ship_id,
        m.move_thrust,
        m.move_angle_deg,
        m.dock_to};
}
