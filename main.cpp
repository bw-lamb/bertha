#include <iostream>

import cards;
import player;

int main()
{
    cards::deck d(1);
    d.shuffle();

    for(const auto &c : d.cards)
    {
        std::cout << c << ' ';
    }
    std::cout << std::endl;

    game::player p1;
    game::player p2;

    p1.hand = d.deal(5);
    p2.hand = d.deal(5);

    for(const auto &c : p1.hand)
    {
        std::cout << c << ' ';
    }
    std::cout << std::endl;

    for(const auto &c : p2.hand)
    {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
    
    for(const auto &c : d.cards)
    {
        std::cout << c << ' ';
    }
    std::cout << std::endl;

    return 0;
}