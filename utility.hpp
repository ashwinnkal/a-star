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
#include <algorithm>


namespace utility {
    enum struct labels {
        terrain = 0,
        empty = 1,
        closed = 2,
        pathway = 3,
        start = 4,
        goal = 5
    };

    std::unordered_map<labels, std::string> labelMeans = {{labels::terrain, "T"},
                                                          {labels::empty,   "."},
                                                          {labels::closed,  "#"},
                                                          {labels::pathway, "*"},
                                                          {labels::start,   "?"},
                                                          {labels::goal,    "$"}};

    // Logging methods helper
    void logMessage(const std::string &message, std::ofstream &logFile) {
        logFile << message << std::endl;
    }

    // helpers for extractLines
    std::vector<labels> parser(std::string &some_string) {

        std::istringstream lineBuffer(some_string);
        std::vector<labels> temp;
        int num;
        char ch;

        while (lineBuffer >> num) {
            if (num == 0)
                temp.push_back(labels::empty);
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

    //search method helpers.
    bool checkCell(int &a, int &b, std::vector<std::vector<labels>> &grid) {
        bool check_a = (a >= 0 && a < grid.size());
        bool check_b = (b >= 0 && b < grid[0].size());

        if (check_a && check_b)
            return grid[a][b] == labels::empty;

        return false;
    }

    void sortQue(std::vector<std::vector<int>> &list) {
        std::sort(list.begin(), list.end(), [](const auto a, const auto b) {
            return (a[2] + a[3]) > (b[2] + b[3]);
        });

    }

    void addToList(int a, int b, int cost, int heuristic,
                   std::vector<std::vector<int>> &list,
                   std::vector<std::vector<labels>> &grid, std::ofstream &logFile) {

        list.push_back(std::vector<int>{a, b, cost, heuristic});
        logMessage("Adding node to queue: (" + std::to_string(a) + ", " + std::to_string(b) +
                   ") with cost: " + std::to_string(cost) + " and heuristic: " + std::to_string(heuristic), logFile);
        grid[a][b] = labels::closed;
    }

    int heuristicEst(int a1, int b1, int a2, int b2) {
        return std::abs(a2 - a1) + std::abs(b2 - b1);
    }

    void expandNeighbors(std::vector<int> &current,
                         std::vector<std::vector<int>> &list,
                         const std::tuple<int, int> &goal,
                         std::vector<std::vector<labels>> &grid, std::ofstream &logFile) {

        int command[4][2] = {{-1, 0},
                            {0,  -1},
                            {1,  0},
                            {0,  1}};
        int x1 = current[0];
        int y1 = current[1];
        int g = current[2];

        auto [x2, y2] = goal;

        for (auto &i: command) {
            int a = x1 + i[0];
            int b = y1 + i[1];

            if (checkCell(a, b, grid)) {
                int G = g + 1;
                int H = heuristicEst(a, b, x2, y2);
                logMessage("Expanding to neighbor at (" + std::to_string(a) + ", " + std::to_string(b) +
                           ") with G: " + std::to_string(G) + " and H: " + std::to_string(H), logFile);
                addToList(a, b, G, H, list, grid, logFile);

            }
        }
    }

    //Search method
    std::vector<std::vector<labels>> aSearch(std::vector<std::vector<labels>> &grid,
                                             const std::tuple<int, int> &start,
                                             const std::tuple<int, int> &goal) {

        // Logging essentials
        std::ofstream logFile("../log.txt");
        if (!logFile.is_open()) {
            std::cerr << "Failed to open log file." << std::endl;

        }


        //extract start & goal positions.
        auto [x1, y1] = start;
        auto [x2, y2] = goal;

        //set default G and H values.
        int g = 0;
        int h = heuristicEst(x1, y1, x2, y2);

        std::vector<std::vector<int>> que{};
        addToList(x1, y1, g, h, que, grid, logFile);

        //check until all queued items exists.
        while (!que.empty()) {
            sortQue(que);
            auto header = que.back();
            que.pop_back();
            int x = header[0];
            int y = header[1];
            grid[x][y] = labels::pathway;
            logMessage("Current node: (" + std::to_string(x) + ", " + std::to_string(y) + ")", logFile);


            if (x == x2 && y == y2) {
                grid[x1][y1] = labels::start;
                grid[x2][y2] = labels::goal;
                return grid;
            }

            expandNeighbors(header, que, goal, grid, logFile);
        }

        std::cout << "No path found";
        logMessage("No path found", logFile);
        logFile.close();
        return std::vector<std::vector<labels>>{};
    }

}

#endif //A_UTILITY_HPP
