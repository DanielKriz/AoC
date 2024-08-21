#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

constexpr int STACK_SIZE = 9;

std::string getValueBetweenBrackets(const std::string &str) {
    return std::isspace(str[0]) ? "" : str.substr(str.find("[") + 1, 1);
}

std::tuple<int, int, int> parseCommand(const std::string &cmd) {
    std::stringstream ss(cmd);
    std::string word = "";
    std::vector<int> positions;
    // We want every second word
    while (ss >> word && ss >> word) {
        positions.push_back(std::stoi(word));
    }
    return std::make_tuple(positions[0], --positions[1], --positions[2]);
}

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::string line = "";
    std::array<std::vector<std::string>, STACK_SIZE> stacks;
    while (std::getline(file, line) && !line.empty()) {
        for (int i = 0, j = 0; i < line.length(); i += 4, ++j) {
            auto value = getValueBetweenBrackets(line.substr(i, 3));
            if (!value.empty()) {
                stacks[j].push_back(value);
            }
        }
    }
    for (auto &stack : stacks) {
        std::reverse(stack.begin(), stack.end());
    }

    while (std::getline(file, line)) {
        auto [count, from, to] = parseCommand(line);
        for (int i = 0; i < count; ++i) {
            stacks[to].push_back(stacks[from].back());
            stacks[from].pop_back();
        }
    }

    for (const auto &stack : stacks) {
        std::cout << stack.back();
    }
    std::cout << std::endl;

    return 0;
}
