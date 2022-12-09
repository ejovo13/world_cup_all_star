#include "team.hpp"
#include "world_cup.hpp"
#include <algorithm>
#include <assert.h>
#include <random>

#include "match.hpp"
#include "rng.hpp"
// #include ""

using namespace world_cup;


// Let's go ahead and take the top 32 teams

int main() {

    // We want to try and load all of the teams into memory using a csv file

    auto teams48 = Team::top_48();
    assert(teams48.size() == 48);

    std::cout << "Selected teams: \n";


    for (auto& t : teams48) {
        std::cout << t << "\n";
    } 

    Match match(teams48.at(0), teams48.at(1));
    auto res = match.simulate();
    std::cout << res << "\n";

    // Let's shuffle pools randomly

    // return a permutation of n values
    auto perm = rng::permutation(48);

    for (auto i : perm) {
        std::cout << i << " ";
    }

    // with this permutation and the top 48 teams, let's now create some pools
    auto gen_pools = [&] (const std::vector<Team> &t48, const std::vector<int> &permutation) -> std::vector<Pool> {

        std::vector<Pool> out (0);

        for (int __i = 0; __i < 48; __i += 4) {
            int i0 = permutation.at(__i);
            int i1 = permutation.at(__i + 1);
            int i2 = permutation.at(__i + 2);
            int i3 = permutation.at(__i + 3);
            Pool p (t48.at(i0), t48.at(i1), t48.at(i2), t48.at(i3));
            out.push_back(p);
        }

        return out;
    };

    auto pools = gen_pools(teams48, perm);

    for (auto &p : pools) {
        std::cout << p << "\n";
    }

    /**========================================================================
     *!                           Simulation of pools
     *========================================================================**/
    std::cout << "Simulating Pools\n";
    for (auto &p : pools) {
        std::cout << p.run_round_robin() << "\n";
    }

    // We break this apart into chunks of 4 and call them pools

    return 0;
}