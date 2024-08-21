#include <algorithm>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <sstream>
#include <string_view>
#include <utility>
#include <vector>

namespace aoc {
struct Monkey {
    Monkey(
        int testValue,
        std::pair<int, int> operands,
        std::pair<int, int> monkeys,
        std::vector<int> items,
        std::function<std::size_t(std::size_t, std::size_t)> operation
    )
        : testValue_(testValue)
        , monkeys_(monkeys)
        , operands_(operands)
        , operation_(operation) {
        for (const auto &item : items) {
            items_.push_back(item);
        }
        inspectionCnt = 0;
    }

    // pair of throw item to monkey
    std::vector<std::pair<int, std::size_t>> evaluate(std::size_t commonMultiply) {
        std::vector<std::pair<int, std::size_t>> ret;
        while (!items_.empty()) {
            std::size_t item = items_.front();
            items_.pop_front();
            ++inspectionCnt;
            if (operands_.first == 0 && operands_.second == 0) {
                item = operation_(item, item);
            } else if (operands_.first == 0) {
                item = operation_(item, operands_.second);
            } else if (operands_.second == 0) {
                item = operation_(operands_.first, item);
            } else {
                item = operation_(operands_.first, operands_.second);
            }

            item = item % commonMultiply;
            if (item % testValue_ == 0) {
                ret.emplace_back(monkeys_.first, item);
            } else {
                ret.emplace_back(monkeys_.second, item);
            }
        }
        return ret;
    }

    std::deque<std::size_t> items_;
    int testValue_;
    std::pair<int, int> monkeys_;
    std::pair<std::size_t, std::size_t> operands_;
    std::function<std::size_t(std::size_t, std::size_t)> operation_;
    std::size_t inspectionCnt;
};

std::vector<int> extractNumbers(std::string &line) {
    // May the god forgive me this C++98 monstrosity
    std::regex reNumber("([0-9]+)|(old)");
    std::match_results<decltype(line.begin())> match;
    auto it = std::sregex_iterator {
        line.begin(),
        line.end(),
        reNumber
    };
    std::vector<int> ret;
    for (decltype(it) last; it != last; ++it) {
        if ((it->str() == "old")) {
            ret.push_back(0);
        } else {
            ret.push_back(std::stoi(it->str()));
        }
    }
    return ret;
}

std::function<std::size_t(std::size_t, std::size_t)> extractOperation(std::string &line) {
    if (std::regex_search(line, std::regex("\\+"))) {
        return [](std::size_t x, std::size_t y) { return x + y; };
    } else {
        return [](std::size_t x, std::size_t y) { return x * y; };
    }
}

int findHighestCommonFactor(int x, int y) {
    while (x != y) {
        if (x > y) {
            x -= y;
        } else {
            y -= x;
        }
    }
    return x;
}

} // namespace aoc

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::vector<aoc::Monkey> monkeys;
    std::string line = "";
    std::regex numberRegex;

    while (std::getline(file, line)) {
        if (line == "") {
            continue;
        }
        std::vector<int> tmp;
        std::vector<int> items;
        int testValue;
        std::pair<int, int> monkeyPair;
        std::pair<int, int> operands;
        std::getline(file, line);
        items = aoc::extractNumbers(line);
        std::getline(file, line);
        tmp = aoc::extractNumbers(line);
        operands = { tmp[0], tmp[1] };
        auto operation = aoc::extractOperation(line);
        std::getline(file, line);
        tmp = aoc::extractNumbers(line);
        testValue = tmp[0];
        std::getline(file, line);
        tmp = aoc::extractNumbers(line);
        monkeyPair.first = tmp[0];
        std::getline(file, line);
        tmp = aoc::extractNumbers(line);
        monkeyPair.second = tmp[0];
        monkeys.emplace_back(
            testValue,
            operands,
            monkeyPair,
            items,
            operation
        );
    }
    std::size_t commonMultiply = 1;
    for (const auto &monkey : monkeys) {
        commonMultiply *= monkey.testValue_;
    }

    for (int i = 0; i < 10'000; ++i) {
        for (auto &m : monkeys) {
            auto actions = m.evaluate(commonMultiply);
            if (actions.empty()) {
                continue;
            }
            for (auto &action : actions) {
                monkeys[action.first].items_.push_back(action.second);
            }
        }
    }

    std::vector<std::size_t> tmp;
    for (auto &m : monkeys) {
        tmp.push_back(m.inspectionCnt);
    }
    std::sort(tmp.begin(), tmp.end(), std::greater<std::size_t>());
    std::cout << tmp[0] * tmp[1] << std::endl;
    return 0;
}
