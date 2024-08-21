#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

namespace aoc {
template <typename T>
using grid = std::vector<std::vector<T>>;
using coord = std::pair<std::size_t, std::size_t>;
using CostMap = std::map<aoc::coord, double>;
using PathMap = std::map<aoc::coord, aoc::coord>;

inline int areaToNumber(const char &area) { return area - 'a' + 1; }

double heurestics(
    std::pair<long long, long long> start,
    std::pair<long long, long long> dest
) {
    return std::sqrt(
        std::pow(std::abs(static_cast<double>(start.first - dest.first)), 2)
        + std::pow(std::abs(static_cast<double>(start.second - dest.second)), 2)
    );
}

template <typename T>
bool inGrid(aoc::grid<T> &grid, aoc::coord coords) {
    if (coords.first < 0 or coords.second < 0)
        return false;
    if (coords.second >= grid[0].size() or coords.first >= grid.size())
        return false;
    return true;
}

template <typename T>
bool isPassableTo(aoc::grid<T> &grid, aoc::coord const &curr, aoc::coord const &dest) {
    if ((grid[dest.first][dest.second] - grid[curr.first][curr.second]) > 1)
        return false;
    return true;
}

template <typename T>
std::vector<aoc::coord> generateNeighbors(aoc::grid<T> &grid, aoc::coord &coord) {
    std::vector<aoc::coord> neighbors;
    if (inGrid(grid, { coord.first, coord.second - 1 }))
        neighbors.push_back({ coord.first, coord.second - 1 });
    if (inGrid(grid, { coord.first, coord.second + 1 }))
        neighbors.push_back({ coord.first, coord.second + 1 });
    if (inGrid(grid, { coord.first - 1, coord.second }))
        neighbors.push_back({ coord.first - 1, coord.second });
    if (inGrid(grid, { coord.first + 1, coord.second }))
        neighbors.push_back({ coord.first + 1, coord.second });
    return neighbors;
}

template <typename T>
std::vector<aoc::coord> aStar(
    aoc::grid<T> &grid,
    aoc::coord &start,
    aoc::coord &dest
) {
    std::vector<aoc::coord> open;
    aoc::CostMap gScore;
    aoc::CostMap fScore;
    aoc::PathMap pathMap;

    open.push_back(start);
    while (!open.empty()) {
        std::sort(open.begin(), open.end(), [&fScore](auto x, auto y) {
            if (fScore.find(x) == fScore.end())
                fScore[x] = 9999;
            if (fScore.find(y) == fScore.end())
                fScore[y] = 9999;
            return fScore[x] > fScore[y];
        });
        auto curr = open.back();
        open.pop_back();

        if (curr.first == dest.first && curr.second == dest.second) {
            std::vector<aoc::coord> path = { curr };
            while (pathMap.find(curr) != pathMap.end()) {
                curr = pathMap[curr];
                path.push_back(curr);
            }
            return path;
            // reconstruct path
        }
        for (const auto &neighbor : aoc::generateNeighbors(grid, curr)) {
            if (!isPassableTo(grid, curr, neighbor)) {
                continue;
            }
            if (gScore.find(neighbor) == gScore.end())
                gScore[neighbor] = 9999;
            const auto tentativeScore = gScore[curr] + 1;
            if (tentativeScore < gScore[neighbor]) {
                pathMap[neighbor] = curr;
                gScore[neighbor] = tentativeScore;
                fScore[neighbor] = static_cast<double>(tentativeScore) + heurestics(neighbor, dest);
                fScore[neighbor] = tentativeScore + heurestics(neighbor, dest);
                if (std::find(open.begin(), open.end(), neighbor) == open.end()) {
                    open.push_back(neighbor);
                }
            }
        }
    }
    return {}; // return empty vector, if no path to destination found
}
} // namespace aoc

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    aoc::coord end;
    aoc::grid<int> grid;
    std::string line = "";
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (const auto &area : line) {
            if (area == 'S') {
                row.push_back(aoc::areaToNumber('a'));
            } else if (area == 'E') {
                end = std::make_pair(grid.size(), row.size());
                row.push_back(aoc::areaToNumber('z'));
            } else {
                row.push_back(aoc::areaToNumber(area));
            }
        }
        grid.push_back(row);
    }

    std::set<aoc::coord> starts;
    for (int i = 0; i < grid.size(); ++i) {
        starts.insert({ i, 0 });
        starts.insert({ i, grid[0].size() - 1 });
    }
    for (int i = 0; i < grid[0].size(); ++i) {
        starts.insert({ 0, i });
        starts.insert({ grid.size() - 1, i });
    }

    std::size_t shortest = 999;
    for (auto start : starts) {
        if (grid[start.first][start.second] != 1) {
            continue;
        }
        auto path = aoc::aStar(grid, start, end);
        if (path.size() == 0) {
            continue;
        }
        if (path.size() - 1 < shortest) {
            shortest = path.size() - 1;
        }
    }
    std::cout << shortest << std::endl;

    return 0;
}
