#pragma once

namespace advent21 {

bool CompareInts(char key, int val1, int val2) {
    if (key == '1') {
        return val1 >= val2;
    } else {
        return val1 <= val2;
    }
} 

template <typename T>
std::string Part2(const std::vector<std::string>& vecString, const char P) {
    std::string buffer {};
    int m = vecString.size();

    std::vector<int> indices (m);
    std::iota(indices.begin(), indices.end(), 0);

    int j = 0;
    while (indices.size() > 1) {
        int index_1 = 0;

        //stores the index of the majority
        std::vector<int> v1s;
        std::vector<int> v0s;

        for(const auto& i : indices) {
            char a = vecString[i][j];
            if (a == '1') {
                index_1++;
                v1s.push_back(i);
            } else {
                v0s.push_back(i);
            }
        }

        if (P == 'o') {
            if (index_1 >= indices.size()-index_1) {
                indices = v1s;
            } else {
                indices = v0s;
            }
        } else {
            if (index_1 < indices.size()-index_1) {
                indices = v1s;
            } else {
                indices = v0s;
            }
        }
        buffer = vecString[indices[0]];
        j++;
    }

    return buffer;
}

template<typename T>
class Sol03 : public Base {
public:
    Sol03(const std::string&);
    void Solution1();
    void Solution2();
private:
    std::vector<std::vector<T>> obj;
};


template<typename T>
Sol03<T>::Sol03(const std::string& nums)
: Base(nums) { }

template<typename T>
void Sol03<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, ',');
    std::vector<T> vecString = vTFromVVT<T>(obj);

    std::string gammas {};
    std::string epsilons {};

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
    std::vector<T> vecString = vTFromVVT<T>(obj);
    std::string o2s = Part2<void>(vecString, 'o');
    std::string co2s = Part2<void>(vecString, 'c');

    int o2i = std::stoi(o2s, nullptr, 2);
    int co2i = std::stoi(co2s, nullptr, 2);

    std::cout << o2s << ' ' << co2s << '\n';
    std::cout << o2i << ' ' << co2i << '\n';
    std::cout << o2i * co2i << " solution2" << std::endl;
}

}