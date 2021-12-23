#pragma once

namespace advent21 {

int convolve(const int i, const int j, const std::vector<std::string>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    std::vector<int> compared {};
    int here = grid[i][j]-'0';
    // north
    if (!(i < 1)) {
        compared.push_back(grid[i-1][j]-'0');
    }
    // south
    if (!(i > m-2)) {
        compared.push_back(grid[i+1][j]-'0');
    }
    // west
    if (!(j < 1)) {
        compared.push_back(grid[i][j-1]-'0');
    }
    // east
    if (!(j > n-2)) {
        compared.push_back(grid[i][j+1]-'0');
    }
    for (const auto& val : compared) {
        if (val <= here) {
            return 0;
        }
    }
    std::cout << i << ' ' << j << ' ' << here << '\n';
    return here+1;
}

bool look(size_t i, size_t j,
          const std::vector<std::string>& out,
          std::vector<std::vector<bool>>& checked,
          int& size) {
        
    if (out[i][j] != '9' && !checked[i][j] ) {
        size++;
    } else {
        return 0;
    }
    checked[i][j] = true;

    if (!(i < 1)) {
        look(i-1, j, out, checked, size);
    }
    if (!(i > out.size()-2)) {
        look(i+1, j, out, checked, size);
    }
    if (!(j < 1)) {
        look(i, j-1, out, checked, size);
    }
    if (!(j > out[0].size()-2)) {
        look(i, j+1, out, checked, size);
    }
    return true;
}


template<typename T>
class Sol09 : public Base {
public:
    Sol09(const std::string&);
    void Solution1();
    void Solution2();
    T Day09();
private:
    std::vector<std::vector<T>> obj;
};

template<typename T>
Sol09<T>::Sol09(const std::string& nums)
: Base(nums) { }

template<typename T>
T Sol09<T>::Day09() {
    return {};
}

template<typename T>
void Sol09<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, ',');
    std::vector<std::string> out = vTFromVVT<T>(obj);
    int sum = 0;
    // max indexes
    int n = out[0].size();
    int m = out.size();
    std::cout << "n: " << n << "\tm: " << m << '\n';
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            sum += convolve(i, j, out);
        }
    }

    // 9483 too high
    // 9780 too high
    // 1636 too high
    std::cout << sum << " solution1" << std::endl;
}


template<typename T>
void Sol09<T>::Solution2() {
    std::vector<std::string> out = vTFromVVT<T>(obj);
    std::vector<std::vector<bool>> checked(out.size(), std::vector<bool>(out[0].size(), false));
    int m = out.size();
    int n = out[0].size();
    std::vector<int> container {};
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (!checked[i][i]) {
                int sum = 0;
                look(i, j, out, checked, sum);
                container.push_back(sum);
            }
        }
    }

    std::sort(container.begin(), container.end());
    int product = 1;
    for (auto rit = container.rbegin(); rit != container.rbegin()+3; rit++) {
        product *= *rit;
    }
    std::cout << product << " solution2" << std::endl;
}

}
