#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

const int KNOT_COUNT = 10;

namespace aoc {

struct Knot {
    int x;
    int y;

    Knot()
        : x(0)
        , y(0) { }

    std::pair<int, int> getPosition() const {
        return std::make_pair(x, y);
    }

    bool isDiagonal(Knot &next) {
        if (x == next.x || y == next.y)
            return false;
        return true;
    }

    void moveInDirection(char direction) {
        switch (direction) {
        case 'U':
            x--;
            break;
        case 'D':
            x++;
            break;
        case 'L':
            y--;
            break;
        case 'R':
            y++;
        }
    }

    void moveToNext(Knot &next) {
        if (std::abs(x - next.x) <= 1 && std::abs(y - next.y) <= 1)
            return;
        if (isDiagonal(next)) {
            // it is attached diagonally
            if (x > next.x && y > next.y) {
                --x;
                --y;
            } else if (x > next.x && y < next.y) {
                --x;
                ++y;
            } else if (x < next.x && y > next.y) {
                ++x;
                --y;
            } else {
                ++x;
                ++y;
            }
        } else {
            if (x > next.x)
                --x;
            else if (x < next.x)
                ++x;
            else if (y > next.y)
                --y;
            else if (y < next.y)
                ++y;
        }
    }
};
} // namespace aoc

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::string line = "";
    std::vector<aoc::Knot> rope;
    for (int i = 0; i < KNOT_COUNT; ++i) {
        rope.emplace_back(aoc::Knot());
    }

    std::set<std::pair<int, int>> tailPositions;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (char direction; ss >> direction) {
            int steps = 0;
            ss >> steps;
            for (int i = 0; i < steps; ++i) {
                rope[0].moveInDirection(direction);
                for (int i = 1; i < rope.size(); ++i) {
                    rope[i].moveToNext(rope[i - 1]);
                }
                tailPositions.insert(rope.back().getPosition());
            }
        }
    }

    std::cout << tailPositions.size() << std::endl;
    return 0;
}
