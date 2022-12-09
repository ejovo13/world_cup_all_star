#pragma once
/**========================================================================
 * ?                          bracket.hpp
 * @brief   : Implementation og Bracket types and infrastructure to assigne
 * different teams to pools
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-08
 *========================================================================**/

// #include "world_cup.hpp"
#include "rng.hpp"
#include "team.hpp"
#include "match.hpp"

namespace world_cup {

struct PoolResults {

    Result ab;
    Result ac;
    Result ad;
    Result bc;
    Result bd;
    Result cd;

    int A_wins = 0;
    int A_loss = 0;
    int A_ties = 0;

    int B_wins = 0;
    int B_loss = 0;
    int B_ties = 0;

    int C_wins = 0;
    int C_loss = 0;
    int C_ties = 0;

    int D_wins = 0;
    int D_loss = 0;
    int D_ties = 0;
    
    // Get metrics about the pool results
    auto a_score() const -> int { return A_wins * 3 + A_ties * 1; }
    auto b_score() const -> int { return B_wins * 3 + B_ties * 1; }
    auto c_score() const -> int { return C_wins * 3 + C_ties * 1; }
    auto d_score() const -> int { return D_wins * 3 + D_ties * 1; }

    auto a_goals_scored() const -> int { return ab.home_score + ac.home_score + ad.home_score; }
    auto b_goals_scored() const -> int { return ab.away_score + bc.home_score + bd.home_score; }
    auto c_goals_scored() const -> int { return ac.away_score + bc.away_score + cd.home_score; }
    auto d_goals_scored() const -> int { return ad.away_score + bd.away_score + cd.away_score; }

    auto a_goals_scored_against() const -> int { return ab.away_score + ac.away_score + ad.away_score; }
    auto b_goals_scored_against() const -> int { return ab.home_score + bc.away_score + bd.away_score; }
    auto c_goals_scored_against() const -> int { return ac.home_score + bc.home_score + cd.away_score; }
    auto d_goals_scored_against() const -> int { return ad.home_score + bd.home_score + cd.home_score; }

    auto a() const -> Team { return ab.home; }
    auto b() const -> Team { return bc.home; }
    auto c() const -> Team { return cd.home; }
    auto d() const -> Team { return cd.away; }

};

// We need to convert a PoolResults object into a ranking.
auto conv_PoolResults_to_ranking(const PoolResults& res) -> std::vector<Team>;

std::ostream& operator<<(std::ostream &os, const PoolResults& res);

class Pool {

public:

    Pool() {}
    Pool(Team A, Team B, Team C, Team D) : A_{A}, B_{B}, C_{C}, D_{D} {}

    auto run_round_robin() const -> PoolResults;

    friend std::ostream& operator<<(std::ostream& os, const Pool& pool) {
        os << "A: " << pool.A_.name() << ", B: " << pool.B_.name() << ", C: " << pool.C_.name() << ", D: " << pool.D_.name();
        return os;
    };

    static auto gen_pools(const std::vector<Team> &t48, const std::vector<int> &permutation) -> std::vector<Pool>;

private:

    Team A_;
    Team B_;
    Team C_;
    Team D_;

};

} // namespace world_cup



// clas