#include <regex>

#include "../utils/utils.hpp"

void star1(std::vector<std::string> &lines) {
    std::vector<double> nums;
    int sum = 0;
    for (auto line : lines) {
        if (line == "") {
            auto ax = nums[0], ay = nums[1], bx = nums[2], by = nums[3], px = nums[4], py = nums[5];
            auto ca = (px * by - py * bx) / (ax * by - ay * bx);
            auto cb = (px - ax * ca) / bx;
            if (static_cast<int>(ca) == ca && static_cast<int>(cb) == cb) {
                if (ca < 101 && cb < 101) {
                    sum += ca * 3 + cb;
                }
            }

            nums.clear();
            continue;
        }

        std::regex numRegex("\\d+");
        std::smatch match;
        for (size_t i = 0; i < 2; i++) {
            std::regex_search(line, match, numRegex);
            nums.push_back(std::stod(match.str()));
            line = match.suffix().str();
        }
    }

    std::cout << "Sum 1: " << sum << "\n";
}

void star2(std::vector<std::string> &lines) {
    std::vector<long double> nums;
    long sum = 0;
    for (auto &&line : lines) {
        if (line == "") {
            auto ax = nums[0], ay = nums[1], bx = nums[2], by = nums[3], px = nums[4], py = nums[5];
            px += 10000000000000;
            py += 10000000000000;
            auto ca = (px * by - py * bx) / (ax * by - ay * bx);
            auto cb = (px - ax * ca) / bx;
            if (static_cast<long>(ca) == ca && static_cast<long>(cb) == cb) {
                sum += ca * 3 + cb;
            }

            nums.clear();
            continue;
        }

        std::regex numRegex("\\d+");
        std::smatch match;
        for (size_t i = 0; i < 2; i++) {
            std::regex_search(line, match, numRegex);
            nums.push_back(std::stold(match.str()));
            line = match.suffix().str();
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
    lines->push_back("");

    // star1(lines.value());
    star2(lines.value());

    return 0;
}