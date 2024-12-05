#include <algorithm>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../utils/utils.hpp"

void star1(std::vector<std::string> &lines) {
    std::vector<std::function<bool(std::vector<int>)>> rules;
    std::vector<std::string>::iterator it = lines.begin();
    for (auto line = lines.begin(); line != lines.end(); line++) {
        if (*line == "") {
            it = line;
            break;
        }

        size_t pos = (*line).find("|");
        int num1 = std::stoi((*line).substr(0, pos));
        int num2 = std::stoi((*line).substr(pos + 1));
        rules.push_back([=](std::vector<int> update) -> bool {
            auto it1 = std::find(update.begin(), update.end(), num1);
            auto it2 = std::find(update.begin(), update.end(), num2);
            if (it1 == update.end() || it2 == update.end()) {
                return true;
            }

            if (it2 - update.begin() < it1 - update.begin()) {
                return false;
            }

            return true;
        });
    }

    std::vector<std::vector<int>> updates;
    for (auto line = it + 1; line != lines.end(); line++) {
        std::vector<int> update;
        std::string token;
        std::istringstream iss(*line);
        while (std::getline(iss, token, ',')) {
            update.push_back(std::stoi(token));
        }
        updates.push_back(update);
    }

    int sum = 0;
    std::for_each(updates.begin(), updates.end(), [&](std::vector<int> update) {
        bool ok = true;
        for (auto &rule : rules) {
            if (!rule(update)) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            return;
        }

        sum += update[update.size() / 2];
    });
    std::cout << "Sum 1: " << sum << "\n";

    return;
}

void star2(std::vector<std::string> &lines) {
    std::vector<std::function<std::optional<std::pair<int, int>>(std::vector<int>)>> rules;
    std::vector<std::string>::iterator it = lines.begin();
    for (auto line = lines.begin(); line != lines.end(); line++) {
        if (*line == "") {
            it = line;
            break;
        }

        size_t pos = (*line).find("|");
        int num1 = std::stoi((*line).substr(0, pos));
        int num2 = std::stoi((*line).substr(pos + 1));
        rules.push_back([=](std::vector<int> update) -> std::optional<std::pair<int, int>> {
            auto it1 = std::find(update.begin(), update.end(), num1);
            auto it2 = std::find(update.begin(), update.end(), num2);
            if (it1 == update.end() || it2 == update.end()) {
                return std::nullopt;
            }

            if (it2 - update.begin() < it1 - update.begin()) {
                return std::make_pair(it1 - update.begin(), it2 - update.begin());
            }

            return std::nullopt;
        });
    }

    std::vector<std::vector<int>> updates;
    for (auto line = it + 1; line != lines.end(); line++) {
        std::vector<int> update;
        std::string token;
        std::istringstream iss(*line);
        while (std::getline(iss, token, ',')) {
            update.push_back(std::stoi(token));
        }
        updates.push_back(update);
    }

    int sum = 0;
    int startingSize = updates.size();
    for (size_t i = 0; i < updates.size(); i++) {
        bool ok = true;
        int idx1 = 0, idx2 = 0;
        for (auto &rule : rules) {
            auto result = rule(updates[i]);
            if (result) {
                idx1 = result->first;
                idx2 = result->second;
                ok = false;
                break;
            }
        }

        // find which failed, switch elements, do it again
        if (!ok) {
            std::swap(updates[i][idx1], updates[i][idx2]);
            updates.push_back(updates[i]);
            continue;
        }
        if (i >= startingSize) {
            sum += updates[i][updates[i].size() / 2];
        }
    }

    std::cout << "Sum 1: " << sum << "\n";

    return;
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