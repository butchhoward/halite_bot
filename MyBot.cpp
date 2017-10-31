#include "hlt/hlt.hpp"
#include "bot_utils/log_utils.hpp"
#include "bot_utils/bot_utils.hpp"
#include "bot_utils/planet_ship_info.hpp"

#include <unordered_set>
#include <utility>


int main()
{
    const hlt::Metadata metadata = hlt::initialize("RueTheDog");
    const hlt::PlayerId player_id = metadata.player_id;

    std::vector<hlt::Move> moves;
    planet_ship_info planet_routing;

    
    for (;;)
    {
        planet_routing.clear();
        moves.clear();
        const hlt::Map map = hlt::in::get_map(metadata.map_width, metadata.map_height);

        log_all_planets(map.planets);
        hlt::Log::out() << "\n" << "Ships: " << map.ships.at(player_id).size() << std::endl;
        
        for (const hlt::Ship &ship : map.ships.at(player_id))
        {
            hlt::Log::out() << "ship: " << ship << std::endl;

            if (ship.docking_status != hlt::ShipDockingStatus::Undocked)
            {
                hlt::Log::out() << "ship already docked:" << ship.entity_id << std::endl;
                continue;
            }

            const hlt::possibly<hlt::MoveNC> move = planet_routing.find_a_planet(map, ship, player_id);
            if (move.second)
            {
                moves.push_back(hlt::MoveNC::toMove(move.first));
            }

            // //ship has not been routed to a mine a planet
            // //attack this planet (later find the nearest opponent planet)
            // const hlt::possibly<hlt::Move> move = attack_something(map, planet, ship);
            // if (move.second)
            // {
            //     hlt::Log::out() << "\tramming: " << planet.entity_id << std::endl;
            //     moves.push_back(move.first);
            //     break;
            // }
        }

        if (!hlt::out::send_moves(moves))
        {
            hlt::Log::log("send_moves failed; exiting");
            break;
        }
    }
}
