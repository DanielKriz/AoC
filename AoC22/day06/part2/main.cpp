#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

constexpr std::size_t BUFFER_SIZE = 14;

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::string signal = "";
    std::getline(file, signal);

    int reads = 0;
    while (true) {
        std::string tmp = signal.substr(reads, BUFFER_SIZE);
        std::set<char> buffer { tmp.begin(), tmp.end() };
        if (buffer.size() == BUFFER_SIZE) {
            break;
        }
        ++reads;
    }
    std::cout << reads + BUFFER_SIZE << std::endl;
}
