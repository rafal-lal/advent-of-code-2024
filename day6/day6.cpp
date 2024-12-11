#include <unordered_map>
#include <utility>

#include "../utils/utils.hpp"

void star1(std::vector<std::string> &lines) {
    std::vector<std::vector<std::string>> floor;
    int currI = 0, currJ = 0;
    for (size_t i = 0; i < lines.size(); i++) {
        std::vector<std::string> tiles;
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '^') {
                currI = i;
                currJ = j;
            }
            tiles.push_back(std::string(1, lines[i][j]));
        }
        floor.push_back(tiles);
    }

    int sum = 0;
    auto currDir = utils::Direction::N;
    while (utils::checkDirection<std::string, int>(
        floor, currI, currJ, currDir, [&](std::string tile, int nextI, int nextJ) -> bool {
            if (floor[currI][currJ] != "X") {
                floor[currI][currJ] = "X";
                sum++;
            }
            if (tile != "#") {
                currI = nextI;
                currJ = nextJ;
                return true;
            }
            currDir = static_cast<utils::Direction>((static_cast<int>(currDir) + 2) % 8);

            return true;
        }));

    utils::print2DVector<std::string>(floor);
    std::cout << "Sum 1: " << sum - 1 + 2 << "\n";
}

void star2(std::vector<std::string> &lines) {
    std::vector<std::vector<std::string>> floor;
    int currI = 0, currJ = 0;
    for (size_t i = 0; i < lines.size(); i++) {
        std::vector<std::string> tiles;
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '^') {
                currI = i;
                currJ = j;
            }
            tiles.push_back(std::string(1, lines[i][j]));
        }
        floor.push_back(tiles);
    }
    int startI = currI, startJ = currJ;
    auto startingFloor(floor);

    auto currDir = utils::Direction::N;
    while (utils::checkDirection<std::string, int>(
        floor, currI, currJ, currDir, [&](std::string tile, int nextI, int nextJ) -> bool {
            if (floor[currI][currJ] != "X") {
                floor[currI][currJ] = "X";
            }
            if (tile != "#") {
                currI = nextI;
                currJ = nextJ;
                return true;
            }
            currDir = static_cast<utils::Direction>((static_cast<int>(currDir) + 2) % 8);

            return true;
        }));
    floor[currI][currJ] = "X";
    // utils::print2DVector(floor);

    std::vector<std::vector<std::vector<std::string>>> floors;
    for (size_t i = 0; i < floor.size(); i++) {
        for (size_t j = 0; j < floor[i].size(); j++) {
            if (i == startI && j == startJ) {
                continue;
            }
            if (floor[i][j] == "X") {
                std::vector<std::vector<std::string>> copy(startingFloor);
                copy[i][j] = "#";
                floors.push_back(copy);
            }
        }
    }

    int sum = 0;
    float cnt = 0;
    for (auto &fl : floors) {
        cnt++;
        std::cout << "Progress: " << float(cnt / floors.size()) * 100 << "%\n";
        currI = startI;
        currJ = startJ;
        currDir = utils::Direction::N;
        bool directionChange = false;
        std::unordered_map<std::pair<int, int>, int, utils::PairHash> positions;
        std::vector<std::pair<int, int>> visited;
        while (utils::checkDirection<std::string, int>(
            fl, currI, currJ, currDir, [&](std::string tile, int nextI, int nextJ) -> bool {
                if (!directionChange) {
                    positions[std::make_pair(currI, currJ)]++;
                    if (positions[std::make_pair(currI, currJ)] > 4) {
                        sum++;
                        return false;
                    }
                }

                if (fl[currI][currJ] != "X") {
                    fl[currI][currJ] = "X";
                }

                if (tile != "#") {
                    currI = nextI;
                    currJ = nextJ;
                    directionChange = false;
                    return true;
                }
                currDir = static_cast<utils::Direction>((static_cast<int>(currDir) + 2) % 8);
                directionChange = true;

                return true;
            }));
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
