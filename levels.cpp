module;

#include <cassert>
#include <functional>
#include <optional>
#include <ranges>
#include <set>
#include <vector>
#include <utility>

export module levels;

import cards;

namespace game::levels
{
    export std::pair<std::optional<std::vector<int>>, std::multiset<int>> has_nkind(unsigned n, std::multiset<int> elements)
    {
        std::vector<int> kind;
        for(int i = 0; i < 10; i++)
        {
            if(elements.count(i) == n)
            {
                for(int j = 0; j < n; j++)
                {
                    auto iter = elements.find(i);
                    kind.push_back(elements.extract(iter).value());
                }
                break;
            }
        }
        if(kind.empty())
            return {std::nullopt, elements};
        return {kind, elements};
    }

    export std::pair<std::optional<std::vector<int>>, std::multiset<int>> has_nrun(unsigned n, std::multiset<int> elements)
    {
        std::vector<int> run;
        for(int i = 0; i < 10; i++)
        {
            // Find a run of n
            for(int m = 0; m < n; m++)
            {
                auto f = elements.find(i + m);
                if(f != elements.end())
                {
                    run.push_back(*f);
                }
                else
                {
                    run.clear();
                    break;
                }
            }
            if(run.size() == n)
            {
                for(const auto& v : run)
                    auto _ = elements.extract(v); // erase() erases ALL values of v
                break;
            }
        }

        if(run.empty())
            return {std::nullopt, elements};
        return {run, elements}; 
    }

    export std::pair<std::optional<std::vector<std::vector<int>>>, std::multiset<int>> has_all(
        std::vector<std::function<std::pair<std::optional<std::vector<int>>, std::multiset<int>>(unsigned, std::multiset<int> &)>> funcs,
        std::vector<unsigned> ns,
        std::multiset<int> elements)
    {
        assert(funcs.size() == ns.size());

        auto modified(elements);
        std::vector<std::vector<int>> results;

        for(const auto [f, n] : std::ranges::views::zip(funcs, ns))
        {
            auto [res, m] = f(n, modified);

            if(res == std::nullopt)
                return {std::nullopt, elements};

            results.push_back(res.value());
            modified = m;
        }

        return {results, modified};
    }
}