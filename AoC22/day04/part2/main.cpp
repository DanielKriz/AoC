#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

std::pair<std::string, std::string> splitString(const std::string &str, char delim = ' ') {
    if (int idx = str.find(delim); idx != std::string::npos) {
        return std::make_pair(
            std::string(str.begin(), str.begin() + idx),
            std::string(str.begin() + idx + 1, str.end())
        );
    }
    return std::make_pair("", "");
}

std::tuple<int, int, int, int> getRanges(const std::string &str) {
    auto [firstSchedule, secondSchedule] = splitString(str, ',');
    auto firstRanges = splitString(firstSchedule, '-');
    auto secondRanges = splitString(secondSchedule, '-');
    return std::make_tuple(
        std::stoi(firstRanges.first),
        std::stoi(firstRanges.second),
        std::stoi(secondRanges.first),
        std::stoi(secondRanges.second)
    );
}

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::size_t total = 0;
    std::string elfPair = "";
    while (file >> elfPair) {
        auto [A, B, C, D] = getRanges(elfPair);
        if (A >= C && A <= D)
            ++total;
        else if (B <= D && B >= C)
            ++total;
        else if (C >= A && C <= B)
            ++total;
        else if (D <= B && D >= A)
            ++total;
    }
    std::cout << total << std::endl;
    return 0;
}
