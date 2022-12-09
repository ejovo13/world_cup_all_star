#pragma once

#include <random>

namespace world_cup::rng { // world_cup::rng

    /**========================================================================
     *!                           RNG functions
     *========================================================================**/
    auto getRandomSeed() -> std::seed_seq;
    // get a random value between a and b
    auto runif (int a, int b) -> int;

    // generate an integer according to a poisson distribution of parameter \lambda
    // used to simulate the number of goals scored by a team
    auto rpois (int lambda) -> int;

    auto rexp (double lambda) -> double;

    // return a permutation from 0 to n-1
    auto permutation (int n) -> std::vector<int>;

} // namespace world_cup::rng