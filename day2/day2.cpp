#include <iostream>
#include <optional>
#include <sstream>

#include "../utils/utils.hpp"

void star1(std::vector<std::string> &lines) {
    std::vector<std::vector<u_int32_t>> reports;
    for (const auto &line : lines) {
        std::vector<u_int32_t> nums;
        std::istringstream iss(line);
        u_int32_t number;
        while (iss >> number) nums.push_back(number);

        reports.push_back(nums);
    }

    int safeReports = 0;
    for (const auto &report : reports) {
        bool ascending = false;
        if (report[1] > report[0]) ascending = true;

        bool ok = true;
        for (size_t i = 0; i < report.size() - 1; ++i) {
            if (report[i + 1] <= report[i] && ascending) {
                ok = false;
                break;
            }
            if (report[i + 1] >= report[i] && !ascending) {
                ok = false;
                break;
            }

            if (abs(report[i + 1] - report[i]) > 3 ||
                abs(report[i + 1] - report[i]) < 1) {
                ok = false;
                break;
            }
        }
        if (ok) safeReports++;
    }

    std::cout << "Safe reports: " << safeReports << "\n";

    return;
}

void star2(std::vector<std::string> &lines) {
    std::vector<std::vector<u_int32_t>> reports;
    for (const auto &line : lines) {
        std::vector<u_int32_t> nums;
        std::istringstream iss(line);
        u_int32_t number;
        while (iss >> number) nums.push_back(number);

        reports.push_back(nums);
    }

    int safeReports = 0;
    for (const auto &report : reports) {
        for (size_t i = 0; i < report.size(); ++i) {
            auto modReport = report;
            modReport.erase(modReport.begin() + i);

            bool ok = true;
            bool ascending = false;
            if (modReport[1] > modReport[0]) ascending = true;
            for (size_t j = 0; j < modReport.size() - 1; ++j) {
                if (modReport[j + 1] <= modReport[j] && ascending) {
                    ok = false;
                    break;
                }
                if (modReport[j + 1] >= modReport[j] && !ascending) {
                    ok = false;
                    break;
                }

                if (abs(modReport[j + 1] - modReport[j]) > 3 ||
                    abs(modReport[j + 1] - modReport[j]) < 1) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                safeReports++;
                break;
            } 
        }
    }

    std::cout << "Safe reports part 2: " << safeReports << "\n";

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
