
module;

#include <vector>

import cards;

export module player;

namespace game 
{
    export struct player
    {
        std::vector<cards::card> hand;
        unsigned level;
    };
}