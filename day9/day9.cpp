#include "../utils/utils.hpp"

void star1(std::vector<std::string> &lines) {
    auto line = lines[0];
    char number = 0;
    int id = 0;
    std::vector<int> disk;
    for (size_t i = 0; i < line.size(); i++) {
        number = line[i] - '0';
        if (i % 2 == 0) {
            for (size_t j = 0; j < number; j++) {
                disk.push_back(id);
            }
            id++;
        } else {
            for (size_t j = 0; j < number; j++) {
                disk.push_back(-1);
            }
        }
    }
    bool breakOuter = false;
    auto lastFree = disk.begin();
    for (auto i = disk.end() - 1; i >= disk.begin(); i--) {
        if (*i == -1) {
            continue;
        }
        for (auto j = lastFree; j < disk.end(); j++) {
            if (j - disk.begin() >= i - disk.begin()) {
                breakOuter = true;
                break;
            }
            if (*j == -1) {
                std::iter_swap(i, j);
                lastFree = j;
                disk.pop_back();
                break;
            }
        }
        if (breakOuter) {
            break;
        }
    }

    long sum = 0;
    for (size_t i = 0; i < disk.size(); i++) {
        if (disk[i] == -1) {
            continue;
        }
        sum += i * disk[i];
    }

    std::cout << "Sum 1: " << sum << "\n";
}

void star2(std::vector<std::string> &lines) {
    auto line = lines[0];
    char number = 0;
    int id = 0;
    std::vector<int> disk;
    for (size_t i = 0; i < line.size(); i++) {
        number = line[i] - '0';
        if (i % 2 == 0) {
            for (size_t j = 0; j < number; j++) {
                disk.push_back(id);
            }
            id++;
        } else {
            for (size_t j = 0; j < number; j++) {
                disk.push_back(-1);
            }
        }
    }

    bool breakOuter = false;
    for (auto i = disk.end() - 1; i >= disk.begin(); i--) {
        if (*i == -1) {
            continue;
        }

        int fileId = *i;
        int fileLen = 0;
        std::vector<int>::iterator k;
        for (k = i; k >= disk.begin(); k--) {
            if (*k == -1 || *k != fileId) {
                break;
            }
            fileLen++;
        }

        for (auto j = disk.begin(); j < disk.end(); j++) {
            if (j - disk.begin() >= i - disk.begin() - fileLen) {
                break;
            }

            if (*j == -1) {
                int freeSpaceLen = 0;
                for (auto l = j; l < disk.end(); l++) {
                    if (*l != -1) {
                        break;
                    }
                    freeSpaceLen++;
                }
                if (fileLen > freeSpaceLen) {
                    continue;
                }
                for (auto q = i; q > i - fileLen; q--, j++) {
                    std::iter_swap(q, j);
                }
                break;
            }
        }
        i = k + 1;
        if (breakOuter) {
            break;
        }
    }

    for (auto &&num : disk) {
        std::cout << num << " ";
    }

    long sum = 0;
    for (size_t i = 0; i < disk.size(); i++) {
        if (disk[i] == -1) {
            continue;
        }
        sum += i * disk[i];
    }

    std::cout << "Sum 1: " << sum << "\n";
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