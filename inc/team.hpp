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

namespace world_cup {

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

    // Read in a csv file in an established format
    Team(const std::string &csv_line);

    auto win_rate() const -> double { return total_.win_rate(); }
    auto total_games() const -> int { return total_.games; }
    auto goals_per_game() const -> double { return total_.avg_goals(); }
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


} // namespace world_cup