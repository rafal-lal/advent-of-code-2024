#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace utils {

std::optional<std::vector<std::string>> parseFile(const std::string& filename) {
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

enum class Direction { N, NE, E, SE, S, SW, W, NW };

template <typename T>
bool checkDirection(std::vector<std::vector<T>>& array, const size_t i, const size_t j, const Direction dir,
                    const std::function<bool(T, int, int)>& func) {
    int nextI = 0, nextJ = 0;
    switch (dir) {
        case Direction::N:
            nextI = i - 1;
            nextJ = j;
            break;
        case Direction::NE:
            nextI = i - 1;
            nextJ = j + 1;
            break;
        case Direction::E:
            nextI = i;
            nextJ = j + 1;
            break;
        case Direction::SE:
            nextI = i + 1;
            nextJ = j + 1;
            break;
        case Direction::S:
            nextI = i + 1;
            nextJ = j;
            break;
        case Direction::SW:
            nextI = i + 1;
            nextJ = j - 1;
            break;
        case Direction::W:
            nextI = i;
            nextJ = j - 1;
            break;
        case Direction::NW:
            nextI = i - 1;
            nextJ = j - 1;
            break;
    }

    if (nextI < 0 || nextI >= array.size() || nextJ < 0 || nextJ >= array[0].size()) {
        return false;
    }

    return func(array[nextI][nextJ], nextI, nextJ);
}

template <typename T>
void print2DVector(const std::vector<std::vector<T>>& vec) {
    for (const auto& row : vec) {
        for (const auto& elem : row) {
            std::cout << elem << "";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void generatePermutations(const std::string& symbols, int places, std::string current,
                          std::vector<std::vector<std::string>>& result) {
    if (current.size() == places) {
        std::vector<std::string> permutation;
        for (char symbol : current) {
            permutation.push_back(std::string(1, symbol));
        }
        result.push_back(permutation);
        return;
    }

    for (char symbol : symbols) {
        generatePermutations(symbols, places, current + symbol, result);
    }
}

int distance(std::pair<int, int> first, std::pair<int, int> second) {
    return std::abs(second.first - first.first) + std::abs(second.second - first.second);
}

template <typename T>
bool isIn2DGrid(const std::vector<std::vector<T>>& grid, int i, int j) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) {
        return false;
    }

    return true;
}

}  // namespace utils