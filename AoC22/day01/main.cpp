#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

const int TOP_ELF_CNT = 3;

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::vector<std::size_t> elfCalories;
    std::vector<std::size_t> values;

    std::string line = "";
    while (std::getline(file, line)) {
        if (line.empty()) {
            elfCalories.push_back(std::accumulate(values.begin(), values.end(), 0));
            values.clear();
        } else {
            values.push_back(std::stoi(line));
        }
    }
    // Part 1
    std::cout << *std::max_element(elfCalories.begin(), elfCalories.end()) << std::endl;
    // Part 2
    std::sort(elfCalories.begin(), elfCalories.end(), std::greater<std::size_t>());
    std::cout << std::accumulate(
        elfCalories.begin(),
        elfCalories.begin() + TOP_ELF_CNT,
        0
    ) << std::endl;
    return 0;
}
