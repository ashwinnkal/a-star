//
// Created by Ashwinn.
// This program demonstrates the working of A* search for finding a shortest path on a nxn grid.
//

#include "utility.hpp"
#include <iostream>
#include <vector>
#include <tuple>


int main() {

    //get input from file
    std::string file_path = "input.txt";
    std::cout << "Input Board" << std::endl;
    std::vector<std::vector<utility::labels>> board = utility::extractLines(file_path, std::tuple<int, int>{2, 2}, std::tuple<int, int>{0, 0});
    utility::printBoard(board);
}