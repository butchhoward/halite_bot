#include "hlt/hlt.hpp"
#include "bot_utils/log_utils.hpp"
#include "bot_utils/bot_utils.hpp"
#include "bot_utils/movenc.hpp"
#include "bot_utils/routing.hpp"

#include <unordered_set>
#include <utility>

int main()
{
    const hlt::Metadata metadata = hlt::initialize("RueTheDog");
    const hlt::PlayerId player_id = metadata.player_id;

    Routing ship_routing;
    ship_routing.set_player_id(player_id);
    ship_routing.set_map(metadata.initial_map);

    for (;;)
    {
        const hlt::Map map = hlt::in::get_map(metadata.map_width, metadata.map_height);
        
        ship_routing.set_map(map);
        std::vector<hlt::Move> moves;
                
        for (const hlt::Ship &ship : map.ships.at(player_id))
        {
            hlt::Log::out() << "ship: " << ship << std::endl;

            if (ship.docking_status != hlt::ShipDockingStatus::Undocked)
            {
                hlt::Log::out() << "ship already docked:" << ship.entity_id << std::endl;
                continue;
            }

            const hlt::possibly<MoveNC> move = ship_routing.route_a_ship(ship);
            if (move.second)
            {
                moves.push_back(MoveNC::toMove(move.first));
            }
        }

        if (!hlt::out::send_moves(moves))
        {
            hlt::Log::log("send_moves failed; exiting");
            break;
        }
    }
}
