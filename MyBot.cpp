#include "hlt/hlt.hpp"
#include "log_utils.hpp"
#include "movenc.hpp"
#include "routing.hpp"

#include <unordered_set>
#include <utility>

int main()
{
    const hlt::Metadata metadata = hlt::initialize("RueTheDog");
    const hlt::PlayerId player_id = metadata.player_id;

    Routing ship_routing;
    ship_routing.set_player_id(player_id);
    ship_routing.set_map(metadata.initial_map);
    unsigned int turn_count(0);

    for (;;)
    {
        hlt::Log::out() << "--- NEW TURN --- " << turn_count++ << std::endl;
        
        const hlt::Map map = hlt::in::get_map(metadata.map_width, metadata.map_height);
        
        ship_routing.set_map(map);
        std::vector<hlt::Move> moves;
                
        for (const hlt::Ship &ship : map.ships.at(player_id))
        {
            hlt::Log::out() << "ship: " << ship << std::endl;

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
