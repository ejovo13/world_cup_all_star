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
};

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

private:

    Team A_;
    Team B_;
    Team C_;
    Team D_;

};

} // namespace world_cup



// clas