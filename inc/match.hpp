#pragma once
/**========================================================================
 * ?                          match.hpp
 * @brief   : Represent a game between two teams
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-08
 *========================================================================**/
#include "team.hpp"
#include "rng.hpp"
// #include "bracket.hpp"

namespace world_cup {

enum MatchOutcome { v_home, v_away, tie};

struct Result {

    Result(int home_score, int away_score, const Team& home, const Team& away)
        : home_score{home_score}
        , away_score{away_score}
        , home{home}
        , away{away}
    {}

    int home_score;
    int away_score;
    const Team& home;
    const Team& away;

    auto outcome() const -> MatchOutcome {
        if (home_score > away_score) return v_home;
        else if (home_score < away_score) return v_away;
        else return tie;
    }
};

std::ostream& operator<<(std::ostream &os, const Result &res);

class Match {


public:

    Match(const Team& home, const Team& away) : home_{home}, away_{away} {}

    auto simulate() const -> Result {

        // Simulate a poisson process using minutes as the time intervals.
        // Each team will draw the wait time between scoring
        int home_score = 0; 
        int away_score = 0;
        double home_wait_time = 0;
        double away_wait_time = 0;

        double home_rate = home_.goals_per_minute();
        double away_rate = away_.goals_per_minute();

        const int MATCH_DURATION_MIN = 90;

        // While there is still time left
        while (home_wait_time < MATCH_DURATION_MIN || away_wait_time < MATCH_DURATION_MIN) {

            // Wait time between goals
            home_wait_time += rng::rexp(home_rate);
            away_wait_time += rng::rexp(away_rate);

            if (home_wait_time < MATCH_DURATION_MIN) home_score++;
            if (away_wait_time < MATCH_DURATION_MIN) away_score++;
        }

        Result res(home_score, away_score, home_, away_);

        return res;
    }

private:

    const Team &home_;
    const Team &away_;

};





}; // namespace world_cup