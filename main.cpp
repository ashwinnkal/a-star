//
// Created by Ashwinn.
// This program demonstrates the working of A* search for finding a shortest path on a nxn grid.
//

#include "utility.hpp"
#include <iostream>
#include <vector>
#include <tuple>


int main() {

    // start & goal
    std::tuple<int, int> start = {0, 0};
    std::tuple<int, int> goal = {2, 2};

    //get input from file
    std::string file_path = "input.txt";
    std::cout << "Input Board" << std::endl;
    std::vector<std::vector<utility::labels>> board = utility::extractLines(file_path, start, goal);
    utility::printBoard(board);

    //perform A* search
    std::cout << "Solution: " << std::endl;
    std::vector<std::vector<utility::labels>> solution = utility::aSearch(board, start, goal);
    utility::printBoard(solution);
}