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

template <typename T>
std::size_t computeScenicScore(aoc::grid<T> &grid, const int x, const int y) {
    if (x == 0 || x == grid.size() || y == 0 || y == grid[0].size())
        return 0;

    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    for (int i = x - 1; i >= 0; --i) {
        ++x1;
        if (grid[i][y] >= grid[x][y])
            break;
    }

    for (int i = x + 1; i < grid.size(); ++i) {
        ++x2;
        if (grid[i][y] >= grid[x][y])
            break;
    }

    for (int i = y - 1; i >= 0; --i) {
        ++y1;
        if (grid[x][i] >= grid[x][y])
            break;
    }

    for (int i = y + 1; i < grid[0].size(); ++i) {
        ++y2;
        if (grid[x][i] >= grid[x][y])
            break;
    }
    return x1 * x2 * y1 * y2;
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

    std::size_t maxScenicScore = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            std::size_t scenicScore = computeScenicScore(grid, i, j);
            if (scenicScore > maxScenicScore) {
                maxScenicScore = scenicScore;
            }
        }
    }

    std::cout << maxScenicScore << std::endl;
    return 0;
}
