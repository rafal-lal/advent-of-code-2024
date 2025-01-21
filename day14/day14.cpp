#include <array>
#include <numeric>
#include <regex>

#include "../utils/utils.hpp"

using Point = std::pair<int, int>;

void star1(std::vector<std::string> lines) {
    const int rows = 103;
    const int cols = 101;

    std::array<std::array<int, cols>, rows> floor{};
    std::vector<std::pair<Point, Point>> robots;

    std::regex numRegex(R"([+-]?\d+)");
    std::smatch match;
    std::vector<int> nums;
    for (auto &&line : lines) {
        for (size_t i = 0; i < 4; i++) {
            std::regex_search(line, match, numRegex);
            nums.push_back(std::stod(match.str()));
            line = match.suffix().str();
        }
        robots.push_back(std::make_pair(std::make_pair(nums[0], nums[1]), std::make_pair(nums[2], nums[3])));
        floor[nums[1]][nums[0]]++;
        nums.clear();
    }

    for (size_t i = 0; i < 100; i++) {
        for (auto &&robot : robots) {
            floor[robot.first.second][robot.first.first]--;
            auto newX = robot.first.first + robot.second.first;
            auto newY = robot.first.second + robot.second.second;

            if (newX < 0) {
                newX = cols + newX;
            } else if (newX > cols - 1) {
                newX = 0 + (newX - cols);
            }
            if (newY < 0) {
                newY = rows + newY;
            } else if (newY > rows - 1) {
                newY = 0 + (newY - rows);
            }

            robot.first.first = newX;
            robot.first.second = newY;
            floor[robot.first.second][robot.first.first]++;
        }
    }

    std::array<int, 4> results{};
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if ((i < rows / 2) && (j < cols / 2)) {
                results[0] += floor[i][j];
            } else if ((i < rows / 2) && (j > cols / 2)) {
                results[1] += floor[i][j];
            } else if ((i > rows / 2) && (j < cols / 2)) {
                results[2] += floor[i][j];
            } else if ((i > rows / 2) && (j > cols / 2)) {
                results[3] += floor[i][j];
            }
        }
    }

    std::cout << "Sum 1: " << std::accumulate(results.begin(), results.end(), 1, [](int acc, int num) {
        return num == 0 ? acc : acc * num;
    }) << "\n";
}

void star2(std::vector<std::string> lines) {
    const int rows = 103;
    const int cols = 101;

    std::array<std::array<int, cols>, rows> floor{};
    std::vector<std::pair<Point, Point>> robots;

    std::regex numRegex(R"([+-]?\d+)");
    std::smatch match;
    std::vector<int> nums;
    for (auto &&line : lines) {
        for (size_t i = 0; i < 4; i++) {
            std::regex_search(line, match, numRegex);
            nums.push_back(std::stod(match.str()));
            line = match.suffix().str();
        }
        robots.push_back(std::make_pair(std::make_pair(nums[0], nums[1]), std::make_pair(nums[2], nums[3])));
        floor[nums[1]][nums[0]]++;
        nums.clear();
    }

    long minScore = 9223372036854775807;
    for (size_t i = 0; i < 1000000; i++) {
        for (auto &&robot : robots) {
            floor[robot.first.second][robot.first.first]--;
            auto newX = robot.first.first + robot.second.first;
            auto newY = robot.first.second + robot.second.second;

            if (newX < 0) {
                newX = cols + newX;
            } else if (newX > cols - 1) {
                newX = 0 + (newX - cols);
            }
            if (newY < 0) {
                newY = rows + newY;
            } else if (newY > rows - 1) {
                newY = 0 + (newY - rows);
            }

            robot.first.first = newX;
            robot.first.second = newY;
            floor[robot.first.second][robot.first.first]++;
        }

        std::array<int, 4> results{};
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if ((i < rows / 2) && (j < cols / 2)) {
                    results[0] += floor[i][j];
                } else if ((i < rows / 2) && (j > cols / 2)) {
                    results[1] += floor[i][j];
                } else if ((i > rows / 2) && (j < cols / 2)) {
                    results[2] += floor[i][j];
                } else if ((i > rows / 2) && (j > cols / 2)) {
                    results[3] += floor[i][j];
                }
            }
        }

        auto score = std::accumulate(results.begin(), results.end(), 1,
                                     [](int acc, int num) { return num == 0 ? acc : acc * num; });
        if (score < minScore) {
            minScore = score;
            for (const auto &row : floor) {
                for (const auto &elem : row) {
                    if (elem != 0) {
                        std::cout << "X" << "";
                    } else {
                        std::cout << "." << "";
                    }
                }
                std::cout << "\n";
            }
            int number = 0;
            std::cout << "\n\n\n\n";
            std::cout << "Easter egg?: ";
            std::cin >> number;
            if (number == 1) {
                std::cout << i + 1 << "\n";
                break;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    auto lines = utils::parseFile("input.txt");
    if (!lines) {
        std::cout << "Lines is nullptr\n";
        exit(1);
    }

    star1(lines.value());
    star2(lines.value());

    return 0;
}