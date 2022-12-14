#include "world_cup/match.hpp"

namespace all_star::world_cup {

std::ostream& operator<<(std::ostream &os, const MatchResult &res) {
    os << res.home.name() << "(H) " << res.away.name() << "(A) : " << res.home_score << " " << res.away_score;
    return os;
}

}; // namespace world_cup