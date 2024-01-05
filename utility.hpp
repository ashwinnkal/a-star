//
// Created by Ashwinn.
// Utility library for use with main.cpp. Contains all the functions definitions.
//

#ifndef A_UTILITY_HPP
#define A_UTILITY_HPP

#include <vector>
#include <string>


namespace utility {
    enum struct labels {
        terrain = 0,
        open_path = 1,
        closed_path = 2,
        pathway = 3,
        start = 4,
        goal = 5
    };

    std::vector<labels> parseLine(std::string &some_string);

    std::vector<std::vector<labels>> extractLines(const std::string &some_path,
                                                  std::tuple<int, int> startPosition,
                                                  std::tuple<int, int> endPosition);

    void printBoard(const std::vector<std::vector<labels>> &some_board);

}

#endif //A_UTILITY_HPP
