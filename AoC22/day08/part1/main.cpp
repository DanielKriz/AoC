#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

namespace aoc {
template <typename T>
using grid = std::vector<std::vector<T>>;
}

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    aoc::grid<int> grid;
    std::string line = "";
    while (file >> line) {
        std::stringstream ss(line);
        std::vector<int> row;
        char tmp = 0;
        while (ss >> tmp) {
            row.push_back(std::atoi(&tmp));
        }
        grid.push_back(row);
    }

    std::set<std::pair<int, int>> visibleTrees;
    for (int i = 0; i < grid.size(); ++i) {
        int max = -1;
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] > max) {
                visibleTrees.emplace(i, j);
                max = grid[i][j];
            }
        }
    }

    for (int i = 0; i < grid.size(); ++i) {
        int max = -1;
        for (int j = grid[0].size() - 1; j >= 0; --j) {
            if (grid[i][j] > max) {
                visibleTrees.emplace(i, j);
                max = grid[i][j];
            }
        }
    }

    for (int i = 0; i < grid[0].size(); ++i) {
        int max = -1;
        for (int j = 0; j < grid.size(); ++j) {
            if (grid[j][i] > max) {
                visibleTrees.emplace(j, i);
                max = grid[j][i];
            }
        }
    }

    for (int i = 0; i < grid[0].size(); ++i) {
        int max = -1;
        for (int j = grid.size() - 1; j >= 0; --j) {
            if (grid[j][i] > max) {
                visibleTrees.emplace(j, i);
                max = grid[j][i];
            }
        }
    }

    std::cout << visibleTrees.size() << std::endl;
    return 0;
}
