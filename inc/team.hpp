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

    double win_rate() const { return wins / games; }
    double lose_rate() const { return losses / games; }
    double avg_goals() const { return goals / games; }
};



class Team {

public:

    Team(std::string name, Record home, Record away, Record total) 
        : name_{name}
        , home_{home}
        , away_{away}
        , total_{total}
    {}

    // Read in a csv file in an established format
    // Team(const std::istream& csv_file);
    Team(const std::string &csv_line);

    // read a comma seperated value file name

private:

    std::string name_;
    Record home_;
    Record away_;
    Record total_;

};

} // namespace world_cup