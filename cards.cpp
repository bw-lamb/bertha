module;

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <optional>
#include <random>
#include <vector>

export module cards;

template<size_t L>
consteval std::array<uint8_t, L> make_seq()
{
    std::array<uint8_t, L> seq;
    std::iota(seq.begin(), seq.end(), 0);
    return seq;
}

namespace cards
{
    export enum CARD_VALS_ENUM
    {
        CARD_JOKER = 0,
        CARD_ACE,
        CARD_TWO,
        CARD_THREE,
        CARD_FOUR,
        CARD_FIVE,
        CARD_SIX,
        CARD_SEVEN,
        CARD_EIGHT,
        CARD_NINE,
        CARD_TEN,
        CARD_JACK,
        CARD_QUEEN,
        CARD_KING,
        NUM_REG_CARDS
    };

    export enum CARD_SUITS_ENUM
    {
        SUIT_ACES,
        SUIT_DIAMONDS,
        SUIT_CLUBS,
        SUIT_HEARTS,
        NUM_SUITS
    };

    export constexpr std::array<uint8_t, NUM_REG_CARDS> CARD_VALS = make_seq<NUM_REG_CARDS>();
    static constexpr std::array<char, NUM_REG_CARDS> CARD_VAL_REPR{'J', 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K'};
    export constexpr std::array<uint8_t, NUM_SUITS> CARD_SUITS = make_seq<NUM_SUITS>();
    static constexpr std::array<uint8_t, NUM_SUITS> CARD_SUIT_REPR{'A', 'D', 'C', 'H'};
 
    export struct card
    {
        uint8_t val;
        std::optional<uint8_t> suit;

        card(uint8_t val, std::optional<uint8_t> suit)
        {
            this->val = val;
            this->suit = suit;
        }
    };

    export std::ostream& operator<<(std::ostream& os, const card& c)
    {
        char s; 
        if(c.suit == std::nullopt)
            s = '*';
        else
            s = CARD_SUIT_REPR[c.suit.value()];

        os << s << CARD_VAL_REPR[c.val];
        return os;
    }

    export const struct card JOKER(CARD_JOKER, std::nullopt);

    export class deck
    {
    public:
        std::vector<card> cards;
        std::vector<card> discard;
    public:
        deck(unsigned num_decks = 1)
        {
            assert(num_decks > 0);

            for(auto i = 0; i < num_decks; i++)
            {
                for(const auto& suit : CARD_SUITS)
                {
                    for(const auto& val : CARD_VALS)
                    {
                        cards.push_back(card(val, suit));
                    }
                }
                cards.push_back(JOKER);
                cards.push_back(JOKER);
            }
        }

        void shuffle(void)
        {
            cards.insert(cards.end(), discard.begin(), discard.end());

            std::random_device rdev;
            std::mt19937 gen(rdev());
            std::uniform_int_distribution<> dist(0, cards.size() - 1); // bounds are inclusive

            for(auto i = 0; i < cards.size(); i++)
            {
                uint8_t replace = dist(gen);
                std::swap(cards[i], cards[replace]);
            }
        }

        cards::card draw_one(void)
        {
            assert(!cards.empty());
            card c = cards.back();
            cards.pop_back();
            return c;
        }

        cards::card draw_one_from_discard(void)
        {
            assert(!discard.empty());
            card c = discard.back();
            discard.pop_back();
            return c;
        }

        // Replaces c at the 'top' of discard pile
        void replace(card c)
        {
            discard.push_back(c);
        }

        std::vector<card> deal(unsigned n)
        {
            assert(n > 0 && n <= cards.size());
            std::vector<card> hand;

            for(auto i = 0; i < n; i++)
            {
                hand.push_back(cards.back());
                cards.pop_back();
            }

            return hand;
        }
    };
}