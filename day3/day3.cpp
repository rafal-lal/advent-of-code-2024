#include <iostream>
#include <optional>
#include <regex>
#include <sstream>

#include "../utils/utils.hpp"

void star1(std::vector<std::string> &lines) {
    int sum = 0;
    int mulResult = 1;
    std::smatch matches;
    std::string mulMatch;
    for (const auto &line : lines) {
        std::regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)");
        std::regex mulPattern("(\\d{1,3})");
        for (std::sregex_iterator it(line.begin(), line.end(), pattern), endIt;
             it != endIt; ++it) {
            mulMatch = it->str();
            mulResult = 1;
            for (std::sregex_iterator
                     itt(mulMatch.begin(), mulMatch.end(), mulPattern),
                 endItt;
                 itt != endItt; ++itt) {
                mulResult *= std::stoi(itt->str());
            }
            sum += mulResult;
        }
    }

    std::cout << "Sum: " << sum << "\n";

    return;
}

void star2(std::vector<std::string> &lines) {
    bool enabled = true;
    int sum = 0;
    int mulResult = 1;
    std::regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)|don't|do");
    std::regex mulPattern("(\\d{1,3})");
    std::smatch matches;
    std::string mulMatch;

    for (const auto &line : lines) {
        for (std::sregex_iterator it(line.begin(), line.end(), pattern), endIt;
             it != endIt; ++it) {
            mulMatch = it->str();
            if (mulMatch == "do") {
                enabled = true;
            } else if (mulMatch == "don't") {
                enabled = false;
            } else if (enabled) {
                mulResult = 1;
                for (std::sregex_iterator
                         itt(mulMatch.begin(), mulMatch.end(), mulPattern),
                     endItt;
                     itt != endItt; ++itt) {
                    mulResult *= std::stoi(itt->str());
                }
                sum += mulResult;
            }
        }
    }

    std::cout << "Sum 2: " << sum << "\n";

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