#pragma once
/**========================================================================
 * ?                          match.hpp
 * @brief   : Represent a game between two teams
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-08
 *========================================================================**/
#include "world_cup/team.hpp"
#include "world_cup/rng.hpp"
// #include "bracket.hpp"

namespace all_star::world_cup {

enum MatchOutcome { v_home, v_away, tie };

struct MatchResult {

    MatchResult(int home_score, int away_score, const Team& home, const Team& away)
        : home_score{home_score}
        , away_score{away_score}
        , home{home}
        , away{away}
    {}

    int home_score;
    int away_score;
    Team home;
    Team away;

    auto outcome() const -> MatchOutcome {
        if (home_score > away_score) return v_home;
        else if (home_score < away_score) return v_away;
        else return tie;
    }

    auto winner() const -> Team {
        if (home_score > away_score) return home;
        else if (home_score < away_score) return away;
        else throw std::invalid_argument( "There are no winners" );
    }
};

std::ostream& operator<<(std::ostream &os, const MatchResult &res);

class Match {


public:

    Match(const Team& home, const Team& away) : home_{home}, away_{away} {}

    auto simulate() const -> MatchResult {

        // Simulate a poisson process using minutes as the time intervals.
        // Each team will draw the wait time between scoring
        int home_score = rng::sim_goals(home_.goals_per_minute());
        int away_score = rng::sim_goals(away_.goals_per_minute());

        MatchResult res(home_score, away_score, home_, away_);

        return res;
    }

    auto simulate_no_ties() const -> MatchResult {

        double home_rate = home_.goals_per_minute();
        double away_rate = away_.goals_per_minute();

        // Simulate a poisson process using minutes as the time intervals.
        // Each team will draw the wait time between scoring
        int home_score = rng::sim_goals(home_.goals_per_minute());
        int away_score = rng::sim_goals(away_.goals_per_minute());

        // Draw to see who has a smaller next wait time, and give them an extra point
        if (home_score == away_score) 
            rng::rexp(home_rate) < rng::rexp(away_rate) ? home_score++ : away_score++;

        MatchResult res(home_score, away_score, home_, away_);

        return res;
    }

private:

    Team home_;
    Team away_;

};





}; // namespace all_star::world_cup