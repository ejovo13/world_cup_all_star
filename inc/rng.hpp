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


    // Shuffle the contents of a vector via fischer yates
    // and return a new vector
    template <class X>
    auto shuffle_vec(const std::vector<X> &vec) {
        std::vector<X> shuffled;

        int n = vec.size();
        auto perm = rng::permutation(n);
        // get a permutation 
        for (auto &i : perm) {
            shuffled.push_back(vec[i]);
        }

        return shuffled;
    }

    // Simulate the number of goals that a team scores, given a rate per minute
    auto sim_goals(double goals_per_minute) -> int;


} // namespace world_cup::rng