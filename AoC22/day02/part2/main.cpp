#include <array>
#include <fstream>
#include <iostream>
#include <utility>

// There has to be one more layer of brackets because of some bad specification in C++
std::array<std::array<unsigned int, 3>, 3> resultMatrix = { {
    { 3, 4, 8 },
    { 1, 5, 9 },
    { 2, 6, 7 },
} };

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::size_t totalScore = 0;

    std::pair<char, char> match = { '0', '0' };
    while (file >> match.first && file >> match.second) {
        totalScore += resultMatrix[match.first - 'A'][match.second - 'X'];
    }
    std::cout << totalScore << std::endl;
    return 0;
}
