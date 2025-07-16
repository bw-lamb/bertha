module;

#include <iostream>
#include <set>
#include <vector>

module main;
import cards;
import levels;

using namespace game::levels;

void printvec(std::vector<int> vec)
    {
        std::cout << "{ ";
            for(const auto& v : vec)
            {
                std::cout << v << ' '; 
            }
            std::cout << "}\n";
    }

    int main()
    {
        std::multiset<int> s{1, 1, 1, 1, 2, 4, 4, 4, 5, 6, 7};
        auto [res, s2] = has_all({has_nkind, has_nrun}, {4, 3}, s);

        for(const auto& v : res.value())
        {
            printvec(v);
        }

        std::cout << "{ ";
            for(const auto& v : s2)
            {
                std::cout << v << ' '; 
            }
            std::cout << "}\n";
        return 0;
    }