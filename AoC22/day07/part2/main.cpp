#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

const std::size_t DISK_SIZE = 70'000'000;
const std::size_t UPDATE_SIZE = 30'000'000;

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "error: could not open the file" << std::endl;
        return 1;
    }

    std::map<std::string, std::size_t> sizes;
    std::vector<std::string> path;
    std::string line = "";
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (std::string token; ss >> token && token == "$") {
            if (ss >> token && token == "cd") {
                if (ss >> token && token == "..") {
                    path.pop_back();
                } else {
                    path.push_back(token);
                }
            }
        } else if (token == "dir") {
            continue;
        } else {
            std::string current_path = "";
            for (const auto &key : path) {
                current_path += "." + key;
                sizes[current_path] += std::stoi(token);
            }
        }
    }
    const std::size_t NEEDED_FREE_SPACE = UPDATE_SIZE - (DISK_SIZE - sizes["./"]);

    std::size_t smallest = sizes["./"];
    for (const auto &[_, value] : sizes) {
        if (value >= NEEDED_FREE_SPACE && value < smallest) {
            smallest = value;
        }
    }
    std::cout << smallest << std::endl;
    return 0;
}
