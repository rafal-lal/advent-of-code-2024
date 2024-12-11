#include <queue>
#include <tuple>

#include "../utils/utils.hpp"

using Point = std::tuple<int, int, int>;

const utils::Direction directionArr[4] = {utils::Direction::N, utils::Direction::E, utils::Direction::S,
                                          utils::Direction::W};

void star1(std::vector<std::string> &lines) {
    std::vector<std::vector<int>> topography;
    std::vector<Point> trailhead;
    for (size_t i = 0; i < lines.size(); i++) {
        std::vector<int> row;
        for (size_t j = 0; j < lines[i].size(); j++) {
            int num = std::stoi(std::string(1, lines[i][j]));
            if (num == 0) {
                trailhead.push_back(std::make_tuple(i, j, num));
            }
            row.push_back(num);
        }
        topography.push_back(row);
    }

    int sum = 0;
    std::unordered_map<Point, bool, utils::TupleHash> visited;
    for (auto &&head : trailhead) {
        visited.clear();
        std::queue<Point> queue;
        queue.push(head);

        while (queue.size() != 0) {
            auto curr = queue.front();
            queue.pop();
            if (topography[std::get<0>(curr)][std::get<1>(curr)] == 9) {
                sum++;
                continue;
            }

            for (auto &&dir : directionArr) {
                utils::checkDirection<int, int>(topography, std::get<0>(curr), std::get<1>(curr), dir,
                                                [&](int nextHeight, int nextI, int nextJ) -> bool {
                                                    if (nextHeight == std::get<2>(curr) + 1) {
                                                        auto tuple =
                                                            std::make_tuple(nextI, nextJ, std::get<2>(curr) + 1);
                                                        if (!visited[tuple]) {
                                                            visited[tuple] = true;
                                                            queue.push(tuple);
                                                        }
                                                    }
                                                    return true;
                                                });
            }
        }
    }

    std::cout << "Sum 1: " << sum << "\n";
}

void star2(std::vector<std::string> &lines) {
    std::vector<std::vector<int>> topography;
    std::vector<Point> trailhead;
    for (size_t i = 0; i < lines.size(); i++) {
        std::vector<int> row;
        for (size_t j = 0; j < lines[i].size(); j++) {
            int num = std::stoi(std::string(1, lines[i][j]));
            if (num == 0) {
                trailhead.push_back(std::make_tuple(i, j, num));
            }
            row.push_back(num);
        }
        topography.push_back(row);
    }

    int sum = 0;
    // std::unordered_map<Point, bool, utils::TupleHash> visited;
    for (auto &&head : trailhead) {
        // visited.clear();
        std::queue<Point> queue;
        queue.push(head);

        while (queue.size() != 0) {
            auto curr = queue.front();
            queue.pop();
            if (topography[std::get<0>(curr)][std::get<1>(curr)] == 9) {
                sum++;
                continue;
            }

            for (auto &&dir : directionArr) {
                utils::checkDirection<int, int>(topography, std::get<0>(curr), std::get<1>(curr), dir,
                                                [&](int nextHeight, int nextI, int nextJ) -> bool {
                                                    if (nextHeight == std::get<2>(curr) + 1) {
                                                        auto tuple =
                                                            std::make_tuple(nextI, nextJ, std::get<2>(curr) + 1);
                                                        // if (!visited[tuple]) {
                                                        //     visited[tuple] = true;
                                                            queue.push(tuple);
                                                        // }
                                                    }
                                                    return true;
                                                });
            }
        }
    }

    std::cout << "Sum 2: " << sum << "\n";
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
