#include "world_cup/team.hpp"
#include "world_cup/rng.hpp"
#include <assert.h>
#include <sys/stat.h>

namespace all_star::world_cup {

namespace {

    std::vector<std::string> split(const std::string &str, std::string delim = ",") {

        std::vector<std::string> out (0);

        auto start = 0U;
        auto end = str.find(delim);
        while (end != std::string::npos)
        {
            out.push_back(str.substr(start, end - start));
            start = end + delim.length();
            end = str.find(delim, start);
        }

        out.push_back(str.substr(start, end));

        return out;
    }

} // namespace 

Record operator+(const Record &lhs, const Record &rhs) {

    Record out {lhs.games + rhs.games,
                lhs.wins + rhs.wins,
                lhs.losses + rhs.losses,
                lhs.ties + rhs.ties,
                lhs.goals + rhs.goals,
                lhs.goals_against + rhs.goals_against};

    return out;
}

std::ostream &operator<<(std::ostream& os, const Team& team) {

    os << "[Team] " << team.name_ << " ";
    os << "games: " << team.total_.games << ", wins: " << team.total_.wins << ", win_rate: " << team.win_rate();
    return os;
}



namespace {

    using vec = std::vector<Team>;

    // Returns the pair <top32, leftover> where top32.size() = 32 and leftover.size() = 83 - 32
    [[nodiscard]] auto top_32() -> std::pair<vec, vec> {

        // Start out by retrieving the teams and then selecting the 
        // top 32 win rates of teams that have played at least 10 games
        auto teams = Team::get_teams();
        std::sort(teams.begin(), teams.end(), [&] (const Team& lhs, const Team& rhs) { return lhs.win_rate() > rhs.win_rate(); });

        std::vector<Team> top32(0);
        std::vector<Team> leftover(0);
        int i = 0;

        const int MIN_GAMES = 10;
        auto lam = [&] (auto &t) -> bool {
            if (i < 32 && t.total_games() > MIN_GAMES) {
                i++;
                return true;
            } else {
                return false;
            }
        };

        std::copy_if(teams.begin(), teams.end(), std::back_inserter(top32), lam); i = 0; // take top 32 and reset i
        std::copy_if(teams.begin(), teams.end(), std::back_inserter(leftover), [&] (auto x) { return !lam(x); });

        return std::make_pair<vec, vec> (std::move(top32), std::move(leftover));
    }

    [[nodiscard]] auto get_48(std::pair<vec, vec>& pair) -> vec {

        std::vector<Team> next16 (0);

        std::vector<Team>& leftover = pair.second;

        for (int i = 0; i < 16; i++) {
            // get a random number between 0 and the size of teams - 1
            double draw = rng::runif(0, leftover.size() - 1);
            // std::cout << "draw: " << draw << " < " << leftover.size() << "\n";
            next16.push_back(leftover[draw]);
            leftover.erase(leftover.begin() + draw);
        }
            
        std::vector<Team> all48 (0);

        for (auto& t : pair.first) {
            all48.push_back(t);
        }

        for (auto& t : next16) {
            all48.push_back(t);
        }

        assert(all48.size() == 48);

        return all48;
    }
}


auto Team::top_48() -> std::vector<Team> { 
    
    auto pair = top_32(); 
    return get_48(pair);
}

// We are assuming a standard format of:
// name,games,wins,losses,ties,goals,against,
Team::Team(const std::string &csv_line) {

    // First we split the string apart by its commas
    auto split_elements = split(csv_line, ",");

    // for (auto& str : split_elements) {
    //     std::cout << str << " ";
    // }
    // std::cout << "len: " << split_elements.size() << "\n";

    assert(split_elements.size() == 13);

    name_ = split_elements[0];

    Record home_record(
        stoi(split_elements[1]),
        stoi(split_elements[2]),
        stoi(split_elements[3]),
        stoi(split_elements[4]),
        stoi(split_elements[5]),
        stoi(split_elements[6])
    );

    Record away_record(
        stoi(split_elements[7]),
        stoi(split_elements[8]),
        stoi(split_elements[9]),
        stoi(split_elements[10]),
        stoi(split_elements[11]),
        stoi(split_elements[12])
    );

    home_ = home_record;
    away_ = away_record;
    total_ = home_record + away_record;
}

// test if the file exists
inline bool file_exists (const std::string& name) {
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}

std::vector<Team> Team::load_teams(const std::string &csv_file) {

    std::ifstream file;
    file.open(csv_file);
    std::string line;
    std::vector<Team> out(0);

    if (!file_exists(csv_file)) {
        throw std::invalid_argument(csv_file + " does not exist");
    }

    std::getline(file, line); // skip the first line
    int count = 1;
    // file.getline()

    while (std::getline(file, line))
    {
        out.push_back(Team(line));
        count++;
    }

    file.close();

    // std::cout << "Read " << count << " lines\n";

    return out;
}



}; // namespace all_star::world_cup