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

    /**========================================================================
     *!                           Load Teams
     *========================================================================**/
    // Invite 48 teams using a process that selects the 32 best teams
    // and then 16 random invitees
    auto teams48 = Team::top_48();
    assert(teams48.size() == 48);

    std::cout << "Selected teams: \n";
    for (auto& t : teams48) {
        std::cout << t << "\n";
    } 

    // Test match simulation
    Match match(teams48.at(0), teams48.at(1)); // Simulate a game with Germany and Brazil <- insert joke here???
    auto res = match.simulate();
    std::cout << res << "\n";


    /**========================================================================
     *!                           Generate Pools
     *========================================================================**/
    // return a permutation of n values
    auto perm = rng::permutation(48);
    for (auto i : perm) {
        std::cout << i << " ";
    }

    auto pools = Pool::gen_pools(teams48, perm);
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

    // Extraction of the winners
    // of each pool


    return 0;
}