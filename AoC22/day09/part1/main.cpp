#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

namespace aoc {
struct Head {
    int x;
    int y;
    Head()
        : x(0)
        , y(0) {};

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
};

struct Tail {
    int x;
    int y;
    Head *head;

    Tail(Head *head_ptr)
        : x(0)
        , y(0)
        , head(head_ptr) {};

    std::pair<int, int> getPosition() const {
        return std::make_pair(x, y);
    }

    bool isDiagonal() {
        if (x == head->x || y == head->y)
            return false;
        return true;
    }

    void moveToHead() {
        if (std::abs(x - head->x) <= 1 && std::abs(y - head->y) <= 1)
            return;
        if (isDiagonal()) {
            // it is attached diagonally
            if (x > head->x && y > head->y) {
                --x;
                --y;
            } else if (x > head->x && y < head->y) {
                --x;
                ++y;
            } else if (x < head->x && y > head->y) {
                ++x;
                --y;
            } else {
                ++x;
                ++y;
            }
        } else {
            if (x > head->x)
                --x;
            else if (x < head->x)
                ++x;
            else if (y > head->y)
                --y;
            else if (y < head->y)
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
    aoc::Head head {};
    aoc::Tail tail(&head);
    std::set<std::pair<int, int>> tailPositions;
    tailPositions.insert({ 0, 0 });

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (char direction; ss >> direction) {
            int steps = 0;
            ss >> steps;
            std::cout << line << std::endl;
            for (int i = 0; i < steps; ++i) {
                head.moveInDirection(direction);
                tail.moveToHead();
                tailPositions.insert({ tail.xPos, tail.yPos });
            }
        }
    }

    std::cout << tailPositions.size() << std::endl;
    return 0;
}
