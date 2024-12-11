#include <utility>

#include "../utils/utils.hpp"

void star1(std::vector<std::string> &lines) {
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> antennas;
    std::vector<std::vector<std::string>> grid;
    for (size_t i = 0; i < lines.size(); i++) {
        std::vector<std::string> row;
        for (size_t j = 0; j < lines[i].size(); j++) {
            auto str = std::string(1, lines[i][j]);
            if (str != ".") {
                antennas[str].push_back(std::make_pair<int, int>(i, j));
            }
            row.push_back(str);
        }
        grid.push_back(row);
    }
    int sum = 0;
    utils::print2DVector(grid);
    for (auto &&freq : antennas) {
        for (size_t i = 0; i < freq.second.size() - 1; i++) {
            for (size_t j = i + 1; j < freq.second.size(); j++) {
                int x1, y1, x2, y2;
                int xDist = std::abs(freq.second[i].second - freq.second[j].second);
                int yDist = std::abs(freq.second[i].first - freq.second[j].first);

                if (freq.second[i].second < freq.second[j].second) {
                    x1 = freq.second[i].second - xDist;
                    x2 = freq.second[j].second + xDist;
                } else {
                    x1 = freq.second[i].second + xDist;
                    x2 = freq.second[j].second - xDist;
                }
                if (freq.second[i].first < freq.second[j].first) {
                    y1 = freq.second[i].first - yDist;
                    y2 = freq.second[j].first + yDist;
                } else {
                    y1 = freq.second[i].first + yDist;
                    y2 = freq.second[j].first - yDist;
                }
                auto anti1 = std::make_pair(y1, x1);
                auto anti2 = std::make_pair(y2, x2);

                if (utils::isIn2DGrid(grid, anti1.first, anti1.second)) {
                    if (grid[anti1.first][anti1.second] != "#") {
                        grid[anti1.first][anti1.second] = "#";
                        sum++;
                    }
                }
                if (utils::isIn2DGrid(grid, anti2.first, anti2.second)) {
                    if (grid[anti2.first][anti2.second] != "#") {
                        grid[anti2.first][anti2.second] = "#";
                        sum++;
                    }
                }
            }
        }
    }

    utils::print2DVector(grid);
    std::cout << "Sum 1: " << sum << "\n";
}

void star2(std::vector<std::string> &lines) {
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> antennas;
    std::vector<std::vector<std::string>> grid;
    int sum = 0;
    for (size_t i = 0; i < lines.size(); i++) {
        std::vector<std::string> row;
        for (size_t j = 0; j < lines[i].size(); j++) {
            auto str = std::string(1, lines[i][j]);
            if (str != ".") {
                sum++;
                antennas[str].push_back(std::make_pair<int, int>(i, j));
            }
            row.push_back(str);
        }
        grid.push_back(row);
    }
    utils::print2DVector(grid);
    for (auto &&freq : antennas) {
        for (size_t i = 0; i < freq.second.size() - 1; i++) {
            for (size_t j = i + 1; j < freq.second.size(); j++) {
                int x1, y1, x2, y2;
                int xDist = std::abs(freq.second[i].second - freq.second[j].second);
                int yDist = std::abs(freq.second[i].first - freq.second[j].first);

                for (size_t k = 1; k < 10000; k++) {
                    if (freq.second[i].second < freq.second[j].second) {
                        x1 = freq.second[i].second - (xDist * k);
                        x2 = freq.second[j].second + (xDist * k);
                    } else {
                        x1 = freq.second[i].second + (xDist * k);
                        x2 = freq.second[j].second - (xDist * k);
                    }
                    if (freq.second[i].first < freq.second[j].first) {
                        y1 = freq.second[i].first - (yDist * k);
                        y2 = freq.second[j].first + (yDist * k);
                    } else {
                        y1 = freq.second[i].first + (yDist * k);
                        y2 = freq.second[j].first - (yDist * k);
                    }
                    auto anti1 = std::make_pair(y1, x1);
                    auto anti2 = std::make_pair(y2, x2);

                    bool inGrid1 = false, inGrid2 = false;
                    if (utils::isIn2DGrid(grid, anti1.first, anti1.second)) {
                        inGrid1 = true;
                        if (grid[anti1.first][anti1.second] == ".") {
                            grid[anti1.first][anti1.second] = "#";
                            sum++;
                        }
                    }
                    if (utils::isIn2DGrid(grid, anti2.first, anti2.second)) {
                        inGrid2 = true;
                        if (grid[anti2.first][anti2.second] == ".") {
                            grid[anti2.first][anti2.second] = "#";
                            sum++;
                        }
                    }
                    if (!inGrid1 && !inGrid2) {
                        break;
                    }
                }
            }
        }
    }
    int sum2 = 0;
    for (auto &&i : grid) {
        for (auto &&j : i) {
            if (j != ".") {
                sum2++;
            }
        }
    }

    utils::print2DVector(grid);
    std::cout << "Sum 2: " << sum2 << "\n";
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
