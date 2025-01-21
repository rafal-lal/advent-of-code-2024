#include <sstream>

#include "../utils/utils.hpp"

void star1(std::vector<std::string> &lines) {
    std::vector<long> nums;
    for (auto &&line : lines) {
        std::istringstream iss(line);
        u_int32_t number;
        while (iss >> number) nums.push_back(number);
    }

    auto lastNums(nums);
    for (size_t i = 0; i < 25; i++) {
        std::vector<long> newNums;
        for (size_t i = 0; i < lastNums.size(); i++) {
            if (lastNums[i] == 0) {
                newNums.push_back(1);
            } else if (std::to_string(lastNums[i]).size() % 2 == 0) {
                auto str = std::to_string(lastNums[i]);
                auto left = str.substr(0, str.size() / 2);
                auto right = str.substr(str.size() / 2);
                newNums.push_back(std::stoi(left));
                newNums.push_back(std::stoi(right));
            } else {
                newNums.push_back(lastNums[i] *= 2024);
            }
        }
        lastNums = newNums;
    }

    std::cout << "Result 1: " << lastNums.size() << "\n";
}

void star2(std::vector<std::string> &lines) {
    std::vector<long> nums;
    for (auto &&line : lines) {
        std::istringstream iss(line);
        u_int32_t number;
        while (iss >> number) nums.push_back(number);
    }

    std::unordered_map<std::pair<long, int>, long, utils::PairHash> cache(10000);

    long result = 0;
    std::function<long(const long, int)> process = [&](const long num, int level) -> long {
        if (!level) {
            return 1;
        }

        if (num == 0) {
            return process(1, level - 1);
        }
        if (const auto cached = cache.find({num, level}); cached != cache.end()) {
            return cached->second;
        }

        long a = 0;

        for (long index = num; index; index /= 10) ++a;

        if (a & 1) return cache[{num, level}] = process(num * 2024, level - 1);

        long b = 10;

        while (num / b > b) b *= 10;

        return cache[{num, level}] = process(num / b, level - 1) + process(num % b, level - 1);
    };

    for (const auto &num : nums) {
        result += process(num, 75);
    }

    std::cout << "Result 1: " << result << "\n";
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
