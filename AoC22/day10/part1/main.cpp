#include <fstream>
#include <iostream>
#include <sstream>

long long int checkCycles(int cycles, long long int reg) {
    if (cycles % 40 == 20) {
        return reg * cycles;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    long long cycles = 1;
    std::string line = "";
    long long reg = 1;
    long long total = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (std::string command; ss >> command && command == "addx") {
            int value = 0;
            ss >> value;
            ++cycles;
            total += checkCycles(cycles, reg);
            ++cycles;
            reg += value;
            total += checkCycles(cycles, reg);
        } else {
            ++cycles;
            total += checkCycles(cycles, reg);
        }
    }
    std::cout << total << std::endl;

    return 0;
}
