//
// Created by Ashwinn.
// Utility library for use with main.cpp. Contains all the functions definitions.
//

#ifndef A_UTILITY_HPP
#define A_UTILITY_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>


namespace utility {
    enum struct labels {
        terrain = 0,
        open_path = 1,
        closed_path = 2,
        pathway = 3,
        start = 4,
        goal = 5
    };

    std::unordered_map<labels, std::string> labelMeans = {{labels::terrain,     "T"},
                                                          {labels::open_path,   "."},
                                                          {labels::closed_path, "#"},
                                                          {labels::pathway,     "*"},
                                                          {labels::start,       "?"},
                                                          {labels::goal,        "$"}};

    // helper for extractLines
    std::vector<labels> parser(std::string &some_string) {

        std::istringstream lineBuffer(some_string);
        std::vector<labels> temp;
        int num;
        char ch;

        while (lineBuffer >> num) {
            if (num == 0)
                temp.push_back(labels::open_path);
            else
                temp.push_back(labels::terrain);

            lineBuffer >> ch;
        }

        return temp;
    }

    std::vector<std::vector<labels>> extractLines(const std::string &some_path,
                                                  std::tuple<int, int> &startPosition,
                                                  std::tuple<int, int> &endPosition) {

        std::ifstream myFile(some_path);
        std::string str;
        std::vector<std::vector<labels>> temp;
        std::vector<labels> eachLine;

        if (myFile.is_open()) {

            while (std::getline(myFile, str)) {
                eachLine = parser(str);
                temp.push_back(eachLine);

                if (!eachLine.empty())
                    eachLine.clear();
            }
        }

        //modify start and goal positions
        auto [x1, y1] = startPosition;
        auto [x2, y2] = endPosition;
        temp[x1][y1] = labels::start;
        temp[x2][y2] = labels::goal;

        return temp;
    }

    void printBoard(const std::vector<std::vector<labels>> &some_board) {

        for (const auto &a: some_board) {
            for (auto i: a)
                std::cout << " " << labelMeans[i] << " ";
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<labels>> aSearch(std::vector<std::vector<labels>> &grid,
                                             const std::tuple<int, int> &start,
                                             const std::tuple<int, int> &goal) {
        //extract start & goal positions.
        auto [x1, y1] = start;
        auto [x2, y2] = goal;

        //set default G and H values.

        //check until all queued items exists.
        while(false){};

        std::cout << "No path found";
        return std::vector<std::vector<labels>>{};
    }

}

#endif //A_UTILITY_HPP
