#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace utils {

std::optional<std::vector<std::string>> parseFile(const std::string &filename) {
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

enum class Direction { N, NE, E, SE, S, SW, W, NW, Count };

template <typename T>
bool checkDirection(std::vector<std::vector<T>> &array, const size_t i, const size_t j, const Direction dir,
                    const std::function<bool(T)> &func) {
}

}  // namespace utils