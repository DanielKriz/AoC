#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

struct Group {
    std::string first;
    std::string second;
    std::string third;
};

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::size_t total = 0;
    Group items;
    while (file >> items.first && file >> items.second && file >> items.third) {
        auto first = std::set<char>(items.first.begin(), items.first.end());
        auto second = std::set<char>(items.second.begin(), items.second.end());
        auto third = std::set<char>(items.third.begin(), items.third.end());

        std::vector<char> common1;
        std::set_intersection(
            first.begin(), first.end(),
            second.begin(), second.end(),
            std::back_inserter(common1)
        );

        std::vector<char> common2;
        std::set_intersection(
            common1.begin(), common1.end(),
            third.begin(), third.end(),
            std::back_inserter(common2)
        );

        for (const auto &item : common2) {
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
