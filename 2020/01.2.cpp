#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

constexpr int TARGET = 2020;
using um = std::unordered_set<int>;

template <typename T, typename S>
class Solution {
public:
    T day21(std::ifstream& file, const S& line) {
        um::iterator mapit;
        um::iterator map2it;
        T value = std::stoi(line);
        T others = TARGET - value;
        mapit = map.find(value);
        map2it = map2.find(others);
        if (mapit == map.end()) {
            map.insert(value);
        }
        if (map2it == map2.end()) {
            map2.insert(others);
        }
        for (const auto& i : map) {
            T other = others - i;
            mapit = map.find(other);
            if (mapit != map.end()) {
                file.close();
                return value*i*other;
            }
        }
        return;
    }

    um map;
    um map2;
};

template <typename T, typename S>
T BopIt(const S& s) {
    Solution<T, S> soln;
    std::string line;
    std::ifstream file(s);
    if (file.is_open()) {
        um::iterator mapit;
        while(getline(file, line)) {
            soln.day21(file, line);
        }
        file.close();
    }
    return 0;
}


int main(int argc, char** argv) {
    std::cout << BopIt<int, std::string>(std::string(argv[0]) + std::string(".dat")) << std::endl;
    return 0;
}
