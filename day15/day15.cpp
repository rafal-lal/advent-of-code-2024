#include "../utils/utils.hpp"

using Point = std::pair<int, int>;

void star1(std::vector<std::string> lines) {
    std::vector<std::vector<std::string>> warehouse;
    std::vector<utils::Direction> sequence;

    bool seq = false;
    Point point;
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i] == "") {
            seq = true;
            continue;
        }

        if (!seq) {
            std::vector<std::string> row;
            for (size_t j = 0; j < lines[i].size(); j++) {
                if (lines[i][j] == '@') {
                    point = std::make_pair(i, j);
                }
                row.push_back(std::string(1, lines[i][j]));
            }
            warehouse.push_back(row);
            continue;
        }
        for (auto &&c : lines[i]) {
            if (c == '^') {
                sequence.push_back(utils::Direction::N);
            } else if (c == '>') {
                sequence.push_back(utils::Direction::E);
            } else if (c == 'v') {
                sequence.push_back(utils::Direction::S);
            } else if (c == '<') {
                sequence.push_back(utils::Direction::W);
            }
        }
    }

    for (auto &&step : sequence) {
        std::vector<Point> moveInDirection;
        bool clearAll = false;
        std::function<bool(std::string, int, int)> recursiveCheck = [&](std::string nextTile, int nextI,
                                                                        int nextJ) -> bool {
            if (nextTile == "#") {
                clearAll = true;
                return false;
            } else if (nextTile == ".") {
                utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ));
                return false;
            } else if (nextTile == "O") {
                utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ));
                return utils::checkDirection<std::string, int>(warehouse, nextI, nextJ, step, recursiveCheck);
            }

            return false;
        };

        utils::checkDirection<std::string, int>(warehouse, point.first, point.second, step, recursiveCheck);
        if (clearAll) {
            moveInDirection.clear();
        }
        for (int i = moveInDirection.size() - 1; i >= 0; i--) {
            utils::checkDirection<std::string, int>(
                warehouse, moveInDirection[i].first, moveInDirection[i].second,
                static_cast<utils::Direction>((static_cast<int>(step) + 4) % 8),
                [&](std::string nextTile, int nextI, int nextJ) -> bool {
                    if (nextTile == "@") {
                        point = std::make_pair(moveInDirection[i].first, moveInDirection[i].second);
                    }
                    auto tmp = warehouse[moveInDirection[i].first][moveInDirection[i].second];
                    warehouse[moveInDirection[i].first][moveInDirection[i].second] = warehouse[nextI][nextJ];
                    warehouse[nextI][nextJ] = tmp;
                    return true;
                });
        }
        moveInDirection.clear();
    }

    utils::print2DVector(warehouse);
    int sum = 0;
    for (size_t i = 0; i < warehouse.size(); i++) {
        for (size_t j = 0; j < warehouse[i].size(); j++) {
            if (warehouse[i][j] == "O") {
                sum += 100 * i + j;
            }
        }
    }

    std::cout << "Sum 1: " << sum << "\n";
}

void star2(std::vector<std::string> lines) {
    std::vector<std::vector<std::string>> warehouse;
    std::vector<utils::Direction> sequence;

    bool seq = false;
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i] == "") {
            seq = true;
            continue;
        }

        if (!seq) {
            std::vector<std::string> row;
            for (size_t j = 0; j < lines[i].size(); j++) {
                if (lines[i][j] == '@') {
                    row.push_back("@");
                    row.push_back(".");
                } else if (lines[i][j] == '#') {
                    row.push_back("#");
                    row.push_back("#");
                } else if (lines[i][j] == 'O') {
                    row.push_back("[");
                    row.push_back("]");
                } else if (lines[i][j] == '.') {
                    row.push_back(".");
                    row.push_back(".");
                }
            }
            warehouse.push_back(row);
            continue;
        }
        for (auto &&c : lines[i]) {
            if (c == '^') {
                sequence.push_back(utils::Direction::N);
            } else if (c == '>') {
                sequence.push_back(utils::Direction::E);
            } else if (c == 'v') {
                sequence.push_back(utils::Direction::S);
            } else if (c == '<') {
                sequence.push_back(utils::Direction::W);
            }
        }
    }
    // utils::print2DVector(warehouse);
    Point point;
    utils::findIn2DGrid(warehouse, point.first, point.second, "@");

    int cnt = 0;
    for (auto &&step : sequence) {
        cnt++;
        std::vector<Point> moveInDirection;
        bool clearAll = false;
        std::function<bool(std::string, int, int, utils::Direction, int)> recursiveCheck =
            [&](std::string nextTile, int nextI, int nextJ, utils::Direction dir, int depth) -> bool {
            if (nextTile == "#") {
                clearAll = true;
                return false;
            } else if (nextTile == ".") {
                utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ));
                return false;
            } else if ((nextTile == "]" || nextTile == "[")) {
                if (dir == utils::Direction::E) {
                    utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ));
                    utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ + 1));
                    return utils::checkDirection<std::string, int>(warehouse, nextI, nextJ + 1, step, depth + 1,
                                                                   recursiveCheck);
                } else if (dir == utils::Direction::W) {
                    utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ));
                    utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ - 1));
                    return utils::checkDirection<std::string, int>(warehouse, nextI, nextJ - 1, step, depth + 1,
                                                                   recursiveCheck);
                } else if (dir == utils::Direction::N) {
                    if (nextTile == "]") {
                        utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ));
                        utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ - 1));
                        utils::checkDirection<std::string, int>(warehouse, nextI, nextJ, step, depth + 1,
                                                                recursiveCheck);
                        utils::checkDirection<std::string, int>(warehouse, nextI, nextJ - 1, step, depth + 1,
                                                                recursiveCheck);
                    } else if (nextTile == "[") {
                        utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ));
                        utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ + 1));
                        utils::checkDirection<std::string, int>(warehouse, nextI, nextJ, step, depth + 1,
                                                                recursiveCheck);
                        utils::checkDirection<std::string, int>(warehouse, nextI, nextJ + 1, step, depth + 1,
                                                                recursiveCheck);
                    }
                } else if (dir == utils::Direction::S) {
                    if (nextTile == "]") {
                        utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ));
                        utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ - 1));
                        utils::checkDirection<std::string, int>(warehouse, nextI, nextJ, step, depth + 1,
                                                                recursiveCheck);
                        utils::checkDirection<std::string, int>(warehouse, nextI, nextJ - 1, step, depth + 1,
                                                                recursiveCheck);
                    } else if (nextTile == "[") {
                        utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ));
                        utils::addIfNotExists(moveInDirection, std::make_pair(nextI, nextJ + 1));
                        utils::checkDirection<std::string, int>(warehouse, nextI, nextJ, step, depth + 1,
                                                                recursiveCheck);
                        utils::checkDirection<std::string, int>(warehouse, nextI, nextJ + 1, step, depth + 1,
                                                                recursiveCheck);
                    }
                }

                return false;
            }
            return false;
        };

        utils::checkDirection<std::string, int>(warehouse, point.first, point.second, step, 1, recursiveCheck);
        if (clearAll) {
            moveInDirection.clear();
        }
        // std::sort(moveInDirection.begin(), moveInDirection.end());
        for (int i = moveInDirection.size() - 1; i >= 0; i--) {
            utils::checkDirection<std::string, int>(
                warehouse, moveInDirection[i].first, moveInDirection[i].second,
                static_cast<utils::Direction>((static_cast<int>(step) + 4) % 8),
                [&](std::string nextTile, int nextI, int nextJ) -> bool {
                    // utils::print2DVector(warehouse);

                    if (((step == utils::Direction::N || step == utils::Direction::S) && nextTile == "[" &&
                         !utils::Exists(moveInDirection, std::make_pair(nextI, nextJ + 1))) ||
                        ((step == utils::Direction::N || step == utils::Direction::S) && nextTile == "]" &&
                         !utils::Exists(moveInDirection, std::make_pair(nextI, nextJ - 1)))) {
                        return true;
                    }

                    if (nextTile == "@") {
                        point = std::make_pair(moveInDirection[i].first, moveInDirection[i].second);
                    }
                    auto tmp = warehouse[moveInDirection[i].first][moveInDirection[i].second];
                    warehouse[moveInDirection[i].first][moveInDirection[i].second] = warehouse[nextI][nextJ];
                    warehouse[nextI][nextJ] = tmp;
                    return true;
                });
        }
        // utils::print2DVector(warehouse);
        moveInDirection.clear();
    }

    utils::print2DVector(warehouse);
    int sum = 0;
    for (size_t i = 0; i < warehouse.size(); i++) {
        for (size_t j = 0; j < warehouse[i].size(); j++) {
            if (warehouse[i][j] == "[") {
                sum += 100 * i + j;
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

    // star1(lines.value());
    star2(lines.value());

    return 0;
}