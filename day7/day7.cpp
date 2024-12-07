#include <sstream>
#include <string>

#include "../utils/utils.hpp"

void star1(std::vector<std::string> &lines) {
    const std::string operators = "+*";
    long sum = 0;
    for (const auto &line : lines) {
        size_t colon = line.find(":");
        long result = std::stoll(line.substr(0, colon));
        std::vector<int> nums;
        std::istringstream iss(line.substr(colon + 1));
        int number;
        while (iss >> number) {
            nums.push_back(number);
        }

        std::vector<std::vector<std::string>> permutations;
        utils::generatePermutations(operators, nums.size() - 1, "", permutations);
        for (auto &permutation : permutations) {
            long localResult = 0;
            for (size_t i = 0; i < nums.size() - 1; i++) {
                if (permutation[i] == "+") {
                    if (localResult == 0) {
                        localResult = nums[i] + nums[i + 1];
                        continue;
                    }
                    localResult += nums[i + 1];
                } else if (permutation[i] == "*") {
                    if (localResult == 0) {
                        localResult = nums[i] * nums[i + 1];
                        continue;
                    }
                    localResult *= nums[i + 1];
                }
            }
            if (localResult == result) {
                sum += result;
                break;
            }
        }
    }

    std::cout << "Sum 1: " << sum << "\n";
}

void star2(std::vector<std::string> &lines) {
    const std::string operators = "+*|";
    long sum = 0;
    for (const auto &line : lines) {
        size_t colon = line.find(":");
        long result = std::stoll(line.substr(0, colon));
        std::vector<int> nums;
        std::istringstream iss(line.substr(colon + 1));
        int number;
        while (iss >> number) {
            nums.push_back(number);
        }

        std::vector<std::vector<std::string>> permutations;
        utils::generatePermutations(operators, nums.size() - 1, "", permutations);
        for (auto &permutation : permutations) {
            long localResult = 0;
            for (size_t i = 0; i < nums.size() - 1; i++) {
                if (localResult > result) {
                    break;
                }
                if (permutation[i] == "+") {
                    if (localResult == 0) {
                        localResult = nums[i] + nums[i + 1];
                        continue;
                    }
                    localResult += nums[i + 1];
                } else if (permutation[i] == "*") {
                    if (localResult == 0) {
                        localResult = nums[i] * nums[i + 1];
                        continue;
                    }
                    localResult *= nums[i + 1];
                } else if (permutation[i] == "|") {
                    if (localResult == 0) {
                        localResult = std::stoll(std::to_string(nums[i]) + std::to_string(nums[i + 1]));
                        continue;
                    }
                    localResult = std::stoll(std::to_string(localResult) + std::to_string(nums[i + 1]));
                }
            }
            if (localResult == result) {
                sum += result;
                break;
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