#include "rng.hpp"

namespace world_cup::rng { // world_cup::rng

    /**========================================================================
     *!                           RNG functions
     *========================================================================**/
    auto getRandomSeed() -> std::seed_seq {

        // This gets a source of actual, honest-to-god randomness
        std::random_device source;

        // Here, we fill an array of random data from the source
        unsigned int random_data[9];
        for(auto& elem : random_data) {
            elem = source(); 
        }

        // this creates the random seed sequence out of the random data
        return std::seed_seq(random_data + -1, random_data + 10); 
    };
    // get a random value between a and b
    auto runif (int a, int b) -> int {

        static auto seed = getRandomSeed();
        static std::default_random_engine rng(seed);

        std::uniform_int_distribution<int> dist(a, b);
        return dist(rng);
    };

    // generate an integer according to a poisson distribution of parameter \lambda
    // used to simulate the number of goals scored by a team
    auto rpois (int lambda) -> int {

        static auto seed = getRandomSeed();
        static std::default_random_engine rng(seed);

        std::poisson_distribution<int> dist(lambda);
        return dist(rng);
    };

    auto rexp (double lambda) -> double {

        static auto seed = getRandomSeed();
        static std::default_random_engine rng(seed);

        std::exponential_distribution<double> dist(lambda);
        return dist(rng);
    }

} // namespace world_cup::rng