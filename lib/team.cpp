#include "team.hpp"

namespace world_cup {

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




// We are assuming a standard format of:
// name,games,wins,losses,ties,goals,against,
Team::Team(const std::string &csv_line) {

    // First we split the string apart by it's commas

    auto split_elements = split(csv_line, ",");

}

};