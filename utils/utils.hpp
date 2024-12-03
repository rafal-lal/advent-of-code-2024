#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace utils {
std::optional<std::vector<std::string>> parseFile(const std::string &);
}

std::optional<std::vector<std::string>> utils::parseFile(
    const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error: could not open file " << filename << "\n";
        return std::nullopt;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) lines.push_back(line);

    return lines;
}
