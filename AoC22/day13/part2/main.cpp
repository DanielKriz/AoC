#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <variant>
#include <vector>

namespace aoc {
template <typename T>
struct list {
    list() = default;
    list(T initItem) {
        data.push_back(initItem);
    }
    std::vector<std::variant<T, std::shared_ptr<aoc::list<T>>>> data;
    [[nodiscard]] bool empty() { return data.empty(); }
    bool compare(aoc::list<T> other) {
        for (auto i = data.begin(), j = other.data.begin(); i != data.end(); ++i, ++j) {
            if (j == other.data.end()) {
                return false;
            }
            if (i->index() == j->index()) {
                if (i->index() == 0) {
                    auto lhs = std::get<T>(*i);
                    auto rhs = std::get<T>(*j);
                    if (lhs < rhs) {
                        return true;
                    } else if (lhs > rhs) {
                        return false;
                    }
                } else {
                    auto lhs = std::get<std::shared_ptr<aoc::list<T>>>(*i);
                    auto rhs = std::get<std::shared_ptr<aoc::list<T>>>(*j);
                    if (lhs->empty() and rhs->empty()) {
                        continue;
                    }
                    return lhs->compare(*rhs);
                }
                // numerics
            } else if (i->index() != j->index()) {
                if (i->index() == 0) {
                    aoc::list<T> tmp;
                    tmp.data.push_back(std::get<T>(*i));
                    return tmp.compare(*std::get<std::shared_ptr<aoc::list<T>>>(*j));
                    // j is a list
                } else {
                    aoc::list<T> tmp;
                    tmp.data.push_back(std::get<T>(*j));
                    return std::get<std::shared_ptr<aoc::list<T>>>(*i)->compare(tmp);
                }
            }
        }
        return true;
    }
};

aoc::list<long> constructList(std::string &line) {
    std::istringstream ss(line);
    aoc::list<long> list;
    std::vector<std::shared_ptr<aoc::list<long>>> plunge;
    while (!ss.eof()) {
        if (char c; !std::isdigit(ss.peek()) && ss >> c) {
            if (c == '[') {
                plunge.push_back(std::make_shared<aoc::list<long>>());
            } else if (c == ']') {
                auto tmp = plunge.back();
                plunge.pop_back();
                if (plunge.size() == 0) {
                    list.data.push_back(tmp);
                    continue;
                }
                plunge.back()->data.push_back(tmp);
            }
        } else {
            if (plunge.size() == 0) {
                break;
            }
            long x;
            ss >> x;
            plunge.back()->data.push_back(x);
        }
    }
    return list;
}

template <typename T>
void printList(aoc::list<T> &list) {
    for (const auto &value : list.data) {
        try {
            auto a = std::get<long>(value);
            std::cout << a << " ";
        } catch (std::exception &e) {
            std::cout << "[ ";
            printList(*std::get<std::shared_ptr<aoc::list<T>>>(value));
            std::cout << "] ";
        }
    }
}

} // namespace aoc

int main([[maybe_unused]] int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::string line = "";
    std::vector<aoc::list<long>> packets;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        auto first = aoc::constructList(line);
        std::getline(file, line);
        auto second = aoc::constructList(line);
        packets.push_back(first);
        packets.push_back(second);
    }
    line = "[[2]]";
    packets.push_back(aoc::constructList(line));
    line = "[[6]]";
    packets.push_back(aoc::constructList(line));

    std::sort(packets.begin(), packets.end(), [](auto &a, auto &b) {
        return a.compare(b);
    });

    int idx = 1;
    for (auto &list : packets) {
        std::cout << idx << " ";
        aoc::printList(list);
        std::cout << std::endl;
        ++idx;
    }
}
