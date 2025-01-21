#include <cmath>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
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

template <typename T, typename I>
bool checkDirection(std::vector<std::vector<T>>& array, const I i, const I j, const Direction dir,
                    const std::function<bool(T, I, I)>& func) {
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

template <typename T, typename I>
bool checkDirection(std::vector<std::vector<T>>& array, const I i, const I j, const Direction dir, int depth,
                    const std::function<bool(T, I, I, Direction, I)>& func) {
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

    return func(array[nextI][nextJ], nextI, nextJ, dir, depth);
}

template <typename T>
void print2DVector(const T& vec) {
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
void addIfNotExists(std::vector<T>& vec, const T elem) {
    if (std::find(vec.begin(), vec.end(), elem) == vec.end()) {
        vec.push_back(elem);
    }
}

template <typename T>
bool Exists(std::vector<T>& vec, const T elem) {
    if (std::find(vec.begin(), vec.end(), elem) != vec.end()) {
        return true;
    }
    return false;
}

template <typename Container, typename T>
bool findIn2DGrid(const Container& grid, int& q, int& w, const T elem) {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == elem) {
                q = i, w = j;
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool isIn2DGrid(const std::vector<std::vector<T>>& grid, int i, int j) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) {
        return false;
    }

    return true;
}

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        std::size_t h1 = std::hash<T1>()(p.first);
        std::size_t h2 = std::hash<T2>()(p.second);
        return h1 ^ (h2 << 1);
    }
};

struct TupleHash {
    template <typename... T>
    std::size_t operator()(const std::tuple<T...>& t) const {
        return std::apply(
            [](const auto&... args) {
                std::size_t hash = 0;
                ((hash ^= std::hash<std::remove_cv_t<std::remove_reference_t<decltype(args)>>>()(args) + 0x9e3779b9 +
                          (hash << 6) + (hash >> 2)),
                 ...);
                return hash;
            },
            t);
    }
};

}  // namespace utils