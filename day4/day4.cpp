#include <array>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>

#include "../utils/utils.hpp"

enum class Direction { N, NE, E, SE, S, SW, W, NW, Count };
std::array<std::string, 4> word = {"X", "M", "A", "S"};

// TODO: create generic function that will take 2d vector, i and j, Direction
// and apply a func to it
bool checkDirection(std::vector<std::vector<std::string>> &letters, const size_t i, const size_t j, const Direction dir,
                    const int nextLetterIdx) {
    if (nextLetterIdx >= word.size()) {
        return true;
    }

    std::string nextLetter = "";
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

    if (nextI < 0 || nextI >= letters.size() || nextJ < 0 || nextJ >= letters[0].size()) {
        return false;
    }

    nextLetter = letters[nextI][nextJ];
    if (nextLetter == word[nextLetterIdx]) {
        return checkDirection(letters, nextI, nextJ, dir, nextLetterIdx + 1);
    }

    return false;
}

void star1(std::vector<std::string> &lines) {
    std::vector<std::vector<std::string>> letters;
    for (const auto &line : lines) {
        std::vector<std::string> lineLetters;
        for (char c : line) {
            lineLetters.push_back(std::string(1, c));
        }
        letters.push_back(lineLetters);
    }

    int sum = 0;
    for (size_t i = 0; i < letters.size(); i++) {
        for (size_t j = 0; j < letters[i].size(); j++) {
            if (letters[i][j] != word[0]) {
                continue;
            }
            for (size_t k = 0; k < static_cast<size_t>(Direction::Count); k++) {
                if (checkDirection(letters, i, j, static_cast<Direction>(k), 1)) {
                    sum++;
                }
            }
        }
    }
    std::cout << "Sum: " << sum << "\n";

    return;
}

bool checkDirection2(std::vector<std::vector<std::string>> &letters, const size_t i, const size_t j,
                     const Direction dir, const std::string expected) {
    std::string nextLetter = "";
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

    if (nextI < 0 || nextI >= letters.size() || nextJ < 0 || nextJ >= letters[0].size()) {
        return false;
    }

    nextLetter = letters[nextI][nextJ];
    if (nextLetter == expected) {
        return true;
    }

    return false;
}

void star2(std::vector<std::string> &lines) {
    std::vector<std::vector<std::string>> letters;
    for (const auto &line : lines) {
        std::vector<std::string> lineLetters;
        for (char c : line) {
            lineLetters.push_back(std::string(1, c));
        }
        letters.push_back(lineLetters);
    }

    int sum = 0;
    for (size_t i = 0; i < letters.size(); i++) {
        for (size_t j = 0; j < letters[i].size(); j++) {
            if (letters[i][j] != "A") {
                continue;
            }
            bool WE = false;
            bool EW = false;
            if ((checkDirection2(letters, i, j, Direction::NW, "M") &&
                 checkDirection2(letters, i, j, Direction::SE, "S")) ||
                (checkDirection2(letters, i, j, Direction::NW, "S") &&
                 checkDirection2(letters, i, j, Direction::SE, "M"))) {
                WE = true;
            }
            if ((checkDirection2(letters, i, j, Direction::NE, "M") &&
                 checkDirection2(letters, i, j, Direction::SW, "S")) ||
                (checkDirection2(letters, i, j, Direction::NE, "S") &&
                 checkDirection2(letters, i, j, Direction::SW, "M"))) {
                EW = true;
            }

            if (WE && EW) {
                sum++;
            }
        }
    }
    std::cout << "Sum: " << sum << "\n";

    return;
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