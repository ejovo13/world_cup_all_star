#include "bracket.hpp"

namespace world_cup {

auto operator<<(std::ostream &os, const PoolResults& res) -> std::ostream& {
    os << "A: " << res.A_wins << "-" << res.A_loss << "-" << res.A_ties << "\n";
    os << "B: " << res.B_wins << "-" << res.B_loss << "-" << res.B_ties << "\n";
    os << "C: " << res.C_wins << "-" << res.C_loss << "-" << res.C_ties << "\n";
    os << "D: " << res.D_wins << "-" << res.D_loss << "-" << res.D_ties << "\n";
    return os;
};

auto Pool::run_round_robin() const -> PoolResults {

    // Start off by pairing each team with each other (each team plays 3 games, 3 games take place in total)
    Match ab {A_, B_};
    Match ac {A_, C_};
    Match ad {A_, D_};

    Match bc {B_, C_};
    Match bd {B_, D_};

    Match cd {C_, D_};

    // 6 total matches

    // We have to have an algorithm that determines a winner..
    auto ab_res = ab.simulate();
    auto ac_res = ac.simulate();
    auto ad_res = ad.simulate();
    auto bc_res = bc.simulate();
    auto bd_res = bd.simulate();
    auto cd_res = cd.simulate();

    int A_wins = 0, B_wins = 0, C_wins = 0, D_wins = 0;
    int A_loss = 0, B_loss = 0, C_loss = 0, D_loss = 0;
    int A_ties = 0, B_ties = 0, C_ties = 0, D_ties = 0;

    if (ab_res.outcome() == v_home) { A_wins++; B_loss++; }
    else if (ab_res.outcome() == v_away) {A_wins++; B_loss++; }
    else { A_ties++; B_ties++; }

    if (ac_res.outcome() == v_home) { A_wins++; C_loss++; }
    else if (ac_res.outcome() == v_away) {A_wins++; C_loss++; }
    else { A_ties++; C_ties++; }

    if (ad_res.outcome() == v_home) { A_wins++; D_loss++; }
    else if (ad_res.outcome() == v_away) {A_wins++; D_loss++; }
    else { A_ties++; D_ties++; }

    if (bc_res.outcome() == v_home) { B_wins++; C_loss++; }
    else if (bc_res.outcome() == v_away) {B_wins++; C_loss++; }
    else { B_ties++; C_ties++; }

    if (bd_res.outcome() == v_home) { B_wins++; D_loss++; }
    else if (bd_res.outcome() == v_away) {B_wins++; D_loss++; }
    else { B_ties++; D_ties++; }

    if (cd_res.outcome() == v_home) { C_wins++; D_loss++; }
    else if (cd_res.outcome() == v_away) {C_wins++; D_loss++; }
    else { C_ties++; D_ties++; }

    PoolResults res = {.ab = ab_res, .ac = ac_res, .ad = ad_res,
                       .bc = bc_res, .bd = bd_res, 
                       .cd = cd_res, 
                       .A_wins = A_wins, .A_loss = A_loss, .A_ties = A_ties,
                       .B_wins = B_wins, .B_loss = B_loss, .B_ties = B_ties,
                       .C_wins = C_wins, .C_loss = C_loss, .C_ties = C_ties,
                       .D_wins = D_wins, .D_loss = D_loss, .D_ties = D_ties,
                       };

    return res;   

}

}; // namespace world_cup