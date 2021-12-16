#pragma once

#include <numeric>
//#include "../Base.hpp"

namespace advent21 {

bool CompareInts(char key, int val1, int val2) {
    if (key == '1') {
        return val1 >= val2;
    } else {
        return val1 <= val2;
    }
} 

int Part2(const std::vector<std::string>& vecString, const char P) {
    std::string buffer {};
    int m = vecString.size();

    std::vector<int> indices (m);
    std::iota(indices.begin(), indices.end(), 0);

    int j = 0;
    while (indices.size() > 1) {
        int local_index = 0;
        std::vector<int> vPs;
        std::vector<int> vSs;

        for(const auto& i : indices) {
            char a = vecString[i][j];
            if (a == P) {
                local_index++;
                vPs.push_back(i);
            } else {
                vSs.push_back(i);
            }
        }
        if (CompareInts(P, local_index, indices.size()-local_index)) {
            indices = vPs;
        } else {
            indices = vSs;
        }

        buffer = vecString[*indices.end()];
        j++;
    }

    return std::stoi(buffer, nullptr, 2);
}

template<typename T>
class Sol03 : public Base<T> {
public:
    Sol03(const std::string&);
    void Solution1();
    void Solution2();
};


template<typename T>
Sol03<T>::Sol03(const std::string& nums)
: Base<T>(nums, ' ') { }

template<typename T>
void Sol03<T>::Solution1() {
    std::string gammas {};
    std::string epsilons {};
    std::vector<std::string> vecString = Base<std::string>::vTFromVVS(this->obj);
    int m = vecString.size();
    int n = vecString[0].size();
    for(int j=0; j<n; j++) {

        int gamman = 0;
        for(int i=0; i<m; i++) {
            char a = vecString[i][j];
            if (a == '1') {
                gamman++;
            }
        }
        if (gamman > m/2) {
            gammas += '1';
            epsilons += '0';
        } else {
            gammas += '0';
            epsilons += '1';
        }
    }
    int gammai = std::stoi(gammas, nullptr, 2);
    int epsiloni = std::stoi(epsilons, nullptr, 2);

    std::cout << gammas << ' ' << epsilons << '\n';
    std::cout << gammai << ' ' << epsiloni << '\n';
    std::cout << gammai * epsiloni << " solution1" << std::endl;
}

template<typename T>
void Sol03<T>::Solution2() {
    std::vector<std::string> vecString = Base<std::string>::vTFromVVS(this->obj);
    int part1 = Part2(vecString, '1');
    int part2 = Part2(vecString, '0');
    std::cout << part1 << ' ' << part2 << '\n';
    std::cout << part1 * part2 << " solution2" << std::endl;
}

}