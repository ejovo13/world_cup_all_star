#include <gtest/gtest.h>
#include "world_cup.hpp"

using namespace all_star::world_cup;

/**========================================================================
 *!                           LoadTeams
 *========================================================================**/
TEST(LoadTeams, NumTeamsLoaded) {

    constexpr int NUM_TOTAL_TEAMS = 83;
    const std::string filename = "world_cup_stats.csv";

    auto all_teams = Team::load_teams(filename);
    EXPECT_EQ(all_teams.size(), NUM_TOTAL_TEAMS);

}

TEST(LoadTeams, Italy) {

    // constexpr 
    constexpr int ITALY_TOTAL_GAMES = 83; // True value
    constexpr int ITALY_TOTAL_WINS  = 45; // True value
    constexpr int ITALY_TOTAL_GOALS = 128; // True value
    constexpr int ITALY_POSITION    = 15;

    std::string filename = "world_cup_stats.csv";
    auto all_teams = Team::load_teams(filename);

    // Pick out Italy
    auto italy = all_teams[ITALY_POSITION];

    EXPECT_EQ(italy.total_games(), ITALY_TOTAL_GAMES);
    EXPECT_EQ(italy.win_rate(), (double) ITALY_TOTAL_WINS / ITALY_TOTAL_GAMES);
    EXPECT_EQ(italy.goals_per_game(), (double) ITALY_TOTAL_GOALS / ITALY_TOTAL_GAMES);

}

/**========================================================================
 *!                           Functional
 *========================================================================**/
// Test the functions in world_cup::func
TEST(Functional, Map) {

    // Let's use a simple function that converts integers to doubles
    std::function<double(int)> fn = [&] (int a) -> double {
        return a * a + 2;
    };

    std::vector<int> ints = {1, 4, 5, 2};
    auto ints_mapped = func::map_vec(ints, fn);

    int i = 0;
    for (auto& d : ints_mapped) {
        EXPECT_EQ(d, fn(ints[i]));
        i ++;
    }
}

TEST(Functional, Take) {

    const std::vector<int> VEC = {1, 4, 6, 3, 9, 6, 3};
    const std::vector<int> TAKE_ONE = {1}; 
    const std::vector<int> TAKE_THREE = {1, 4, 6};
    const std::vector<int> TAKE_SIX = {1, 4, 6, 3, 9, 6};

    std::vector<int> vec = {1, 4, 6, 3, 9, 6, 3};

    auto t1 = func::take(vec, 1);
    auto t3 = func::take(vec, 3);
    auto t6 = func::take(vec, 6);
    auto t10 = func::take(vec, 10);

    EXPECT_EQ(t1, TAKE_ONE); 
    EXPECT_EQ(t3, TAKE_THREE); 
    EXPECT_EQ(t6, TAKE_SIX); 
    EXPECT_EQ(t10, VEC); 

}



TEST(Functional, Order) {

    const std::vector<int> VEC = {1, 4, 3, 9, 6};
    const std::vector<int> INCREASING_IND = {0, 2, 1, 4, 3};
    const std::vector<int> DECREASING_IND = {3, 4, 1, 2, 0};

    EXPECT_EQ(func::order(VEC), INCREASING_IND);
    EXPECT_EQ(func::order(VEC, true), DECREASING_IND);

}

/**========================================================================
 *!                           SimulateGames
 *========================================================================**/
TEST(SimulateGames, NoTies) {

    auto teams = Team::get_teams();
    Match m {teams[4], teams[32]};

    auto assert_no_tie = [&] () {
        MatchResult res = m.simulate_no_ties();
        EXPECT_NE(res.outcome(), tie); // Assert that the result is not a tie
    };

    const int nb_games = 10000;
    func::replicate(nb_games, assert_no_tie);

}