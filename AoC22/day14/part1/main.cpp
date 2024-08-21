#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

namespace aoc {
const std::string delimiter = " -> ";
template <typename T, std::size_t N, std::size_t M>
using grid = std::array<std::array<T, N>, M>;
using coord = std::pair<std::size_t, std::size_t>;
enum class tile : char {
    empty = '.',
    rock = '#',
    sand = 'o'
};

constexpr std::size_t GRID_SIZE = 200;

aoc::coord getCoord(std::string &str) {
    if (std::size_t idx = str.find(","); idx != std::string::npos) {
        return std::make_pair(
            std::stoi(std::string(str.begin(), str.begin() + idx)),
            std::stoi(std::string(str.begin() + idx + 1, str.end()))
        );
    }
    return std::make_pair(0, 0);
}
} // namespace aoc

int main([[maybe_unused]] int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::string line = "";
    aoc::grid<aoc::tile, aoc::GRID_SIZE, aoc::GRID_SIZE> grid;
    for (std::size_t i = 0; i < aoc::GRID_SIZE; ++i) {
        for (std::size_t j = 0; j < aoc::GRID_SIZE; ++j) {
            grid[i][j] = aoc::tile::empty;
        }
    }
    std::size_t bottom { 0 };
    while (std::getline(file, line)) {
        std::size_t pos = 0;
        std::vector<std::string> directions;

        while ((pos = line.find(aoc::delimiter)) != std::string::npos) {
            directions.emplace_back(line.substr(0, pos));
            line.erase(0, pos + aoc::delimiter.length());
        }
        directions.emplace_back(line.substr(0, pos));

        for (
            auto it1 = directions.begin(), it2 = it1 + 1;
            it1 != directions.end() - 1;
            ++it1, ++it2
        ) {
            auto coords1 = aoc::getCoord(*it1);
            auto coords2 = aoc::getCoord(*it2);
            // This decreases scope of the problem
            coords1.first -= 400;
            coords2.first -= 400;
            if (coords1.first > coords2.first)
                std::swap(coords1.first, coords2.first);
            if (coords1.second > coords2.second)
                std::swap(coords1.second, coords2.second);

            if (coords2.second > bottom)
                bottom = coords2.second;

            for (std::size_t i = coords1.second; i <= coords2.second; ++i) {
                for (std::size_t j = coords1.first; j <= coords2.first; ++j) {
                    grid[i][j] = aoc::tile::rock;
                }
            }
        }
    }

    std::size_t grains = 0;
    while (true) {
        aoc::coord sandPos = { 100, 0 };
        grid[sandPos.second][sandPos.first] = aoc::tile::sand;
        while (true) {
            if (grid[sandPos.second + 1][sandPos.first] == aoc::tile::empty) {
                sandPos.second++;
            } else if (grid[sandPos.second + 1][sandPos.first - 1] == aoc::tile::empty) {
                sandPos.first--;
                sandPos.second++;
            } else if (grid[sandPos.second + 1][sandPos.first + 1] == aoc::tile::empty) {
                sandPos.first++;
                sandPos.second++;
            } else {
                grid[sandPos.second][sandPos.first] = aoc::tile::sand;
                break;
            }
        }
        if (sandPos.second > bottom) {
            break;
        }
        ++grains;
    }
    std::cout << grains << std::endl;
    return 0;
}
