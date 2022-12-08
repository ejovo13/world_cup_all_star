#include "team.hpp"
#include "world_cup.hpp"
#include <algorithm>
#include <assert.h>
#include <random>

#include "match.hpp"

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


    return 0;
}