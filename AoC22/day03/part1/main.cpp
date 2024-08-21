#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::size_t total = 0;
    std::string items = "";
    while (file >> items) {
        const int half = items.length() / 2;

        auto firstCompartment = std::set<char>(items.begin(), items.begin() + half);
        auto secondCompartment = std::set<char>(items.begin() + half, items.end());

        std::vector<char> common;
        std::set_intersection(
            firstCompartment.begin(), firstCompartment.end(),
            secondCompartment.begin(), secondCompartment.end(),
            std::back_inserter(common)
        );
        for (const auto &item : common) {
            if (item >= 'a') {
                total += item - 'a' + 1;
            } else {
                total += item - 'A' + 27;
            }
        }
    }
    std::cout << total << std::endl;
    return 0;
}
