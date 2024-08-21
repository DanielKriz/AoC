#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

namespace aoc {
template <std::size_t width, std::size_t height>
using display = std::array<std::array<int, width>, height>;

template <std::size_t width, std::size_t height>
void drawPixel(int cycles, int sprite, aoc::display<width, height> &display) {
    if (std::abs((cycles % 40) - sprite) <= 1) {
        display[cycles / 40][cycles % 40] = 1;
    }
}

} // namespace aoc

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    int cycles = 0;
    std::string line = "";
    int sprite = 1;

    aoc::display<40, 6> display;
    for (auto &row : display) {
        row.fill(0);
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (std::string command; ss >> command && command == "addx") {
            int value = 0;
            ss >> value;
            ++cycles;
            aoc::drawPixel(cycles, sprite, display);
            ++cycles;
            sprite += value;
            aoc::drawPixel(cycles, sprite, display);
        } else {
            ++cycles;
            aoc::drawPixel(cycles, sprite, display);
        }
    }

    for (const auto &row : display) {
        for (const auto &pixel : row) {
            if (pixel)
                std::cout << "#";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
