#include "match.hpp"

namespace world_cup {

std::ostream& operator<<(std::ostream &os, const Result &res) {
    os << res.home.name() << "(H) " << res.away.name() << "(A) : " << res.home_score << " " << res.away_score;
    return os;
}

}; // namespace world_cup