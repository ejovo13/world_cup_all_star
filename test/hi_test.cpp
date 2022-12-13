#include "world_cup.hpp"
#include <iostream>
#include <assert.h>

using namespace world_cup;

void test_germany_brazil();
void test_bracket();
void test_goal_rate();
void test_home_away();

int main() {

    test_germany_brazil();
    test_bracket();
    test_goal_rate();
    test_home_away();

    return 0;
}

// Germany won 7-1 against Brazil
void test_germany_brazil() {

    // Let's simulate a thousand matches between germany and brazil and see how often
    // we get a score of 7-1
    auto all_teams = Team::get_teams();
    auto germany = all_teams[13];
    auto brazil  = all_teams[7];

    Match match{germany, brazil};

    int nb_games = 50000;
    int count_seven_one = 0;

    auto sim_game = [&] () { 
        auto res = match.simulate();
        if (res.home_score == 7 && res.away_score == 1) {
            count_seven_one ++;
        }
    };

    func::replicate(nb_games, sim_game);

    std::cout << "Germany vs Brazil\n";
    std::cout << "Simulated " << nb_games << " games, num ocurrences of 7-1: " << count_seven_one << "\n";
    std::cout << "proportion: " << double(count_seven_one) / nb_games << "\n";
    std::cout << "inv proportion: " << nb_games / (double) count_seven_one << "\n";
     
    // The experimental proportional value is ~0.0013
    std::cout << "[test_germany_brazil] passed\n";

}

using namespace world_cup::rng; // shuffle_vec
using namespace world_cup::func; // take

void test_bracket() {

    auto teams = Team::top_48();
    auto shuffled_teams = rng::shuffle_vec(teams);

    auto t16 = take(shuffle_vec(teams), 16);

    // Let's create a bracket with these teams!!!
    BracketRound<16> r1 {t16};

    auto r2 = r1.play_round();
    std::cout << "length r2: " << r2.nb_teams() << "\n";

    auto r3 = r2.play_round();
    std::cout << "length r3: " << r3.nb_teams() << "\n";

    auto r4 = r3.play_round();
    std::cout << "length r4: " << r4.nb_teams() << "\n";

    auto r5 = r4.play_round();
    std::cout << "length r5: " << r5.nb_teams() << "\n";

    // auto r4 = r3.play_round();

    std::cout << "[test_bracket] passed\n";

}


// let's see if the experimentally average goals is close to the theoretical.
void test_goal_rate() {

    auto teams = Team::get_teams();
    auto usa = teams[1];

    std::cout << usa << "\n";

    int n_games = 100000;
    int total_goals = 0;

    auto sim_game = [&] () { total_goals += sim_goals(usa.goals_per_minute()); };

    func::replicate(n_games, sim_game);

    std::cout << "Total goals: " << total_goals << "\n";
    std::cout << "avg goals (exp): " << (double) total_goals / n_games << "\n";
    std::cout << "avg goals (theo): " << usa.goals_per_game() << "\n";

}

void test_home_away() {

    // test if the number of wins is different when home or away

    auto teams = Team::get_teams();
    auto usa = teams[1];
    auto france = teams[0];

    std::cout << usa << "\n";
    std::cout << france << "\n";

    Match uf(usa, france);
    Match fu(france, usa);

    // Let's simulate n games and see how the proportion changes (or doesnt)

    int nb_games = 100000;
    int us_won_home = 0;
    int us_won_away = 0;

    auto sim_game_no_ties = [&] () {

        // Increment USA home win
        MatchResult uf_res = uf.simulate_no_ties();
        if (uf_res.winner() == usa) us_won_home ++;

        // Increment USA away win 
        MatchResult fu_res = fu.simulate_no_ties();
        if (fu_res.winner() == usa) us_won_away ++;
    };

    func::replicate(nb_games, sim_game_no_ties);

    std::cout << "USA home wins: " << us_won_home << "\n";
    std::cout << "USA away wins: " << us_won_away << "\n";

}

