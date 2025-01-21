#include <queue>
#include <tuple>

#include "../utils/utils.hpp"

using Point = std::tuple<int, int, std::string>;

const utils::Direction directionArr[4] = {utils::Direction::N, utils::Direction::E, utils::Direction::S,
                                          utils::Direction::W};

void star1(std::vector<std::string> &lines) {
    std::vector<std::vector<Point>> garden;
    for (size_t i = 0; i < lines.size(); i++) {
        std::vector<Point> row;
        for (size_t j = 0; j < lines[i].size(); j++) {
            row.push_back(std::make_tuple(i, j, std::string(1, lines[i][j])));
        }
        garden.push_back(row);
    }

    int sum = 0;
    std::unordered_map<Point, bool, utils::TupleHash> visited;
    std::vector<Point> currentGroup;
    while (true) {
        currentGroup.clear();
        Point currStart;
        bool found = false;
        for (size_t i = 0; i < garden.size(); i++) {
            if (found) {
                break;
            }
            for (size_t j = 0; j < garden[i].size(); j++) {
                if (!visited[garden[i][j]]) {
                    found = true;
                    currStart = garden[i][j];
                    break;
                }
            }
        }
        if (!found) {
            break;
        }

        std::queue<Point> queue;
        queue.push(currStart);
        visited[currStart] = true;
        currentGroup.push_back(currStart);

        while (queue.size() != 0) {
            auto curr = queue.front();
            queue.pop();

            for (auto &&dir : directionArr) {
                utils::checkDirection<Point, int>(garden, std::get<0>(curr), std::get<1>(curr), dir,
                                                  [&](Point nextPlot, int nextI, int nextJ) -> bool {
                                                      if (std::get<2>(nextPlot) == std::get<2>(curr)) {
                                                          auto tuple = std::make_tuple(nextI, nextJ, std::get<2>(curr));
                                                          if (!visited[tuple]) {
                                                              visited[tuple] = true;
                                                              currentGroup.push_back(tuple);
                                                              queue.push(tuple);
                                                          }
                                                      }
                                                      return true;
                                                  });
            }
        }

        int sharedSides = 0;
        for (auto &&point : currentGroup) {
            for (auto &&dir : directionArr) {
                if (utils::checkDirection<Point, int>(garden, std::get<0>(point), std::get<1>(point), dir,
                                                      [&](Point nextPlot, int nextI, int nextJ) -> bool {
                                                          if (std::get<2>(nextPlot) == std::get<2>(point)) {
                                                              return true;
                                                          }
                                                          return false;
                                                      })) {
                    sharedSides++;
                }
            }
        }
        sum += currentGroup.size() * (currentGroup.size() * 4 - sharedSides);
    }

    std::cout << "Sum 1: " << sum << "\n";
}

void star2(std::vector<std::string> &lines) {
    std::vector<std::vector<Point>> garden;
    for (size_t i = 0; i < lines.size(); i++) {
        std::vector<Point> row;
        for (size_t j = 0; j < lines[i].size(); j++) {
            row.push_back(std::make_tuple(i, j, std::string(1, lines[i][j])));
        }
        garden.push_back(row);
    }

    int sum = 0;
    std::unordered_map<Point, bool, utils::TupleHash> visited;
    std::vector<Point> currentGroup;
    while (true) {
        currentGroup.clear();
        Point currStart;
        bool found = false;
        for (size_t i = 0; i < garden.size(); i++) {
            if (found) {
                break;
            }
            for (size_t j = 0; j < garden[i].size(); j++) {
                if (!visited[garden[i][j]]) {
                    found = true;
                    currStart = garden[i][j];
                    break;
                }
            }
        }
        if (!found) {
            break;
        }

        std::queue<Point> queue;
        queue.push(currStart);
        visited[currStart] = true;
        currentGroup.push_back(currStart);

        while (queue.size() != 0) {
            auto curr = queue.front();
            queue.pop();

            for (auto &&dir : directionArr) {
                utils::checkDirection<Point, int>(garden, std::get<0>(curr), std::get<1>(curr), dir,
                                                  [&](Point nextPlot, int nextI, int nextJ) -> bool {
                                                      if (std::get<2>(nextPlot) == std::get<2>(curr)) {
                                                          auto tuple = std::make_tuple(nextI, nextJ, std::get<2>(curr));
                                                          if (!visited[tuple]) {
                                                              visited[tuple] = true;
                                                              currentGroup.push_back(tuple);
                                                              queue.push(tuple);
                                                          }
                                                      }
                                                      return true;
                                                  });
            }
        }

        int corners = 0;
        for (auto &&point : currentGroup) {
            auto N =
                utils::checkDirection<Point, int>(garden, std::get<0>(point), std::get<1>(point), utils::Direction::N,
                                                  [&](Point nextPlot, int nextI, int nextJ) -> bool {
                                                      if (std::get<2>(nextPlot) == std::get<2>(point)) {
                                                          return true;
                                                      }
                                                      return false;
                                                  });
            auto E =
                utils::checkDirection<Point, int>(garden, std::get<0>(point), std::get<1>(point), utils::Direction::N,
                                                  [&](Point nextPlot, int nextI, int nextJ) -> bool {
                                                      if (std::get<2>(nextPlot) == std::get<2>(point)) {
                                                          return true;
                                                      }
                                                      return false;
                                                  });
            auto S =
                utils::checkDirection<Point, int>(garden, std::get<0>(point), std::get<1>(point), utils::Direction::N,
                                                  [&](Point nextPlot, int nextI, int nextJ) -> bool {
                                                      if (std::get<2>(nextPlot) == std::get<2>(point)) {
                                                          return true;
                                                      }
                                                      return false;
                                                  });
            auto W =
                utils::checkDirection<Point, int>(garden, std::get<0>(point), std::get<1>(point), utils::Direction::N,
                                                  [&](Point nextPlot, int nextI, int nextJ) -> bool {
                                                      if (std::get<2>(nextPlot) == std::get<2>(point)) {
                                                          return true;
                                                      }
                                                      return false;
                                                  });

            sum += currentGroup.size() * (currentGroup.size() * 4 - sharedSides);
        }

        std::cout << "Sum 2: " << sum << "\n";
    }

    int main(int argc, char const *argv[]) {
        auto lines = utils::parseFile("input.txt");
        if (!lines) {
            std::cout << "Lines is nullptr\n";
            exit(1);
        }

        // star1(lines.value());
        star2(lines.value());

        return 0;
    }