#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

constexpr int TARGET = 2020;
using um = std::unordered_set<int>;

template <typename T, typename S>
T BopIt(S s) {
    um map;
    std::string line;
    std::ifstream file(s);
    if (file.is_open()) {
        um::iterator mapit;
        while(getline(file, line)) {
            T value = std::stoi(line);
            T other = TARGET - value;
            std::cout << value << ' ' << other << '\n';
            mapit = map.find(value);
            if (mapit == map.end()) {
                map.insert(value);
            }

            mapit = map.find(other);
            if (mapit != map.end()) {
                file.close();
                return value*other;
            }
        }
        file.close();
    }
    return 0;
}


int main(int argc, char** argv) {
    std::cout << BopIt<int, std::string>(std::string(argv[0]) + std::string(".dat")) << std::endl;
    return 0;
}
