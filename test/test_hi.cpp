#include "world_cup.hpp"
#include <iostream>
#include <assert.h>

using namespace world_cup;

void test_load();
void test_germany_brazil();

int main() {

    test_load();
    test_germany_brazil();

    return 0;
}

void test_top_32() {

}

void test_load() {

    // Load in all of the teams and verify certain information about them
    std::string filename = "world_cup_stats.csv";
    auto all_teams = Team::load_teams(filename);

    // auto all_teams = Team::get_teams();
    std::cout << all_teams.size() << "\n";
    assert(all_teams.size() == 83);

    // Pick out Italy
    auto italy = all_teams[15];

    assert(italy.total_games() == 83);
    assert(italy.win_rate() == 45.0 / 83);
    assert(italy.goals_per_game() == 128.0 / 83);
    std::cout << "[test_load] passed\n";

}

// Germany won 7-1 against Brazil
void test_germany_brazil() {

    // Let's simulate a thousand matches between germany and brazil and see how often
    // we get a score of 7-1
    auto all_teams = Team::get_teams();
    auto germany = all_teams[13];
    auto brazil  = all_teams[7];

    Match match{germany, brazil};

    int nb_games = 100000;
    int count_seven_one = 0;

    for (int i = 0; i < nb_games; i++) {
        auto res = match.simulate();
        if (res.home_score == 7 && res.away_score == 1) {
            count_seven_one ++;
        }
    }

    std::cout << "Germany vs Brazil\n";
    std::cout << "Simulated " << nb_games << " games, num ocurrences of 7-1: " << count_seven_one << "\n";
    std::cout << "proportion: " << double(count_seven_one) / nb_games << "\n";
    std::cout << "inv propoertion: " << nb_games / (double) count_seven_one << "\n";


}