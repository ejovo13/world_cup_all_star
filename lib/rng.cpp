#include "rng.hpp"

namespace all_star::world_cup::rng { // world_cup::rng

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

    // Generate a random permutation from 1 to n using Fisher-Yates shuffling.
    auto permutation(int n) -> std::vector<int> {

        // generate a vector from 0 to n-1
        std::vector<int> lin (n, 0);
        for (int i = 0; i < n; i++) {
            lin[i] = i;
        }

        // now shuffle the elements
        for (int i = n - 1; i > 0; i--) {
            int j = runif(0, i);
            int tmp = lin[i];
            lin[i] = lin[j];
            lin[j] = tmp;
        }

        return lin;
    }

    // Simulate the number of goals that a team scores, given a rate per minute
    auto sim_goals(double goals_per_minute) -> int {

        const int MATCH_DURATION_MIN = 90;
        double elapsed_time = 0;
        int score = 0;

        while (elapsed_time < MATCH_DURATION_MIN) {

            elapsed_time += rexp(goals_per_minute);

            if (elapsed_time < MATCH_DURATION_MIN) score++;
        }

        return score;

    }

} // namespace all_star::world_cup::rng