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
    while (utils::checkDirection<std::string>(
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

    int sum = 0;
    auto currDir = utils::Direction::N;
    while (utils::checkDirection<std::string>(
        floor, currI, currJ, currDir, [&](std::string tile, int nextI, int nextJ) -> bool {
            // utils::print2DVector<std::string>(floor);
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

    std::cout << "Sum 2: " << sum - 1 + 2 << "\n";
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