#pragma once
/**========================================================================
 * ?                          team.hpp
 * @brief   : Specification for the team type
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-08
 *========================================================================**/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

namespace all_star::world_cup {

struct Record {

    int games;
    int wins;
    int losses;
    int ties;
    int goals;
    int goals_against;

    Record()
        : games{0}
        , wins{0}
        , losses{0}
        , ties{0}
        , goals{0}
        , goals_against{0}
    {}

    Record(int __games, int __wins, int __losses, int __ties, int __goals, int __goals_against)
        : games{__games}
        , wins{__wins}
        , losses{__losses}
        , ties{__ties}
        , goals{__goals}
        , goals_against{__goals_against}
    {}

    // auto operator==(const Record& rhs) const -> bool = default;

    auto operator==(const Record& rhs) const -> bool {

        return rhs.games == games &&
               rhs.wins == wins &&
               rhs.losses == losses &&
               rhs.ties == ties &&
               rhs.goals == goals &&
               rhs.goals_against == goals_against;

    }

    double win_rate() const { return (double) wins / games; }
    double lose_rate() const { return (double) losses / games; }
    double avg_goals() const { return (double) goals / games; }

    friend Record operator+(const Record &lhs, const Record &rhs);
};



// auto create_teams(const std::string &csv_file) -> std::vector<Team>;

class Team {

public:

    Team() 
        : name_{""}
    {}

    Team(std::string name, Record home, Record away, Record total) 
        : name_{name}
        , home_{home}
        , away_{away}
        , total_{total}
    {}

    // bool operator==(const Team& rhs) const = default;


    bool operator==(const Team& rhs) const {

        return rhs.name_ == name_ && rhs.home_ == home_ && rhs.total_ == total_ && rhs.away_ == total_;

    }

    // Read in a csv file in an established format
    Team(const std::string &csv_line);

    auto win_rate() const -> double { return total_.win_rate(); }
    auto home_win_rate() const -> double { return home_.win_rate(); }
    auto away_win_rate() const -> double { return away_.win_rate(); }

    void print_rates() const {
        std::cout << name_ << " home wr: " << home_win_rate() << ", away wr: " << away_win_rate() << "\n";
    }


    auto total_games() const -> int { return total_.games; }
    auto goals_per_game() const -> double { return total_.avg_goals(); }
    auto goals_per_minute() const -> double { return total_.avg_goals() / 90.0; } 
    auto name() const -> std::string { return name_; }

    // read a comma seperated value file name
    friend std::ostream &operator<<(std::ostream& os, const Team& team);

    static auto load_teams(const std::string &csv_file) -> std::vector<Team>;

    static auto get_teams() -> std::vector<Team> {

        std::string filename = "world_cup_stats.csv";
        return load_teams(filename);
    }

    static auto top_48() -> std::vector<Team>;

    // static auto 



private:

    std::string name_;
    Record home_;
    Record away_;
    Record total_;

};


} // namespace all_star::world_cup