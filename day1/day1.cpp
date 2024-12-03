#include <algorithm>
#include <iostream>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/utils.hpp"

void star1() {
    auto lines = utils::parseFile("input.txt");
    if (!lines) {
        exit(1);
    }

    std::vector<u_int32_t> left, right;
    for (const auto& line : *lines) {
        u_int32_t leftNum, rightNum;

        std::istringstream iss(line);
        if (iss >> leftNum >> rightNum) {
            left.push_back(leftNum);
            right.push_back(rightNum);
        } else {
            exit(1);
        }
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    u_int32_t diff = 0;
    for (size_t i = 0; i < left.size(); ++i) {
        diff += abs(left[i] - right[i]);
    }
    std::cout << "Distance: " << diff << "\n";

    return;
}

void star2() {
    auto lines = utils::parseFile("input.txt");
    if (!lines) {
        exit(1);
    }

    std::vector<u_int32_t> left, right;
    for (const auto& line : *lines) {
        u_int32_t leftNum, rightNum;

        std::istringstream iss(line);
        if (iss >> leftNum >> rightNum) {
            left.push_back(leftNum);
            right.push_back(rightNum);
        } else {
            exit(1);
        }
    }

    u_int32_t similarity = 0;
    for (const auto& leftNum : left) {
        u_int32_t occurrences = 0;
        for (const auto& rightNum : right)
            if (leftNum == rightNum) occurrences++;
        similarity += leftNum * occurrences;
    }
    std::cout << "Similarity: " << similarity << "\n";

    return;
}

int main(int argc, char const* argv[]) {
    star1();
    star2();

    return 0;
}
