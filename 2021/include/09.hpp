#pragma once

namespace advent21 {
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
    int n = out[0].size()-1;
    int m = out.size()-1;
    std::cout << "n: " << n << "\tm: " << m << '\n';
    for (int i=1; i<m-1; i++) {
        for (int j=1; j<n-1; j++) {
            int H = (int)out[i][j];
            int N = (int)out[i-1][j];
            int S = (int)out[i+1][j];
            int E = (int)out[i][j+1];
            int W = (int)out[i][j-1];
            if (H<N && H<S && H<E && H<W) {
                std::cout << i << ',' << j << '\n';
                sum += H+1;
            }

        }
    }
    std::cout << "north " << '\n';
    // north wall
    for (int j=1; j<n-1; j++) {
        int H = (int)out[0][j];
        int S = (int)out[1][j];
        int E = (int)out[0][j+1];
        int W = (int)out[0][j-1];
        if (H<S && H<E && H<W) {
            std::cout << 0 << ',' << j << '\n';
            sum += H+1;
        }
    }
    std::cout << "south " << '\n';
    // south wall
    for (int j=1; j<n-1; j++) {
        int H = (int)out[m][j];
        int N = (int)out[m-1][j];
        int E = (int)out[m][j+1];
        int W = (int)out[m][j-1];
        if (H<N && H<E && H<W) {
            std::cout << m << ',' << j << '\n';
            sum += H+1;
        }
    }
    std::cout << "east " << '\n';
    // east wall
    for (int i=1; i<m-1; i++) {
        int H = (int)out[i][n];
        int N = (int)out[i-1][n];
        int S = (int)out[i+1][n];
        int W = (int)out[i][n-1];
        if (H<N && H<S && H<W) {
            std::cout << i << ',' << n << '\n';
            sum += H+1;
        }
    }
    std::cout << "west " << '\n';
    // west wall
    for (int i=1; i<m-1; i++) {
        int H = (int)out[i][0];
        int N = (int)out[i-1][0];
        int S = (int)out[i+1][0];
        int E = (int)out[i][1];
        if (H<N && H<S && H<E) {
            std::cout << i << ',' << 0 << '\n';
            sum += H+1;
        }
    }
    int H, N, S, E, W;
    // northwest corner
    H = (int)out[0][0];
    S = (int)out[1][0];
    E = (int)out[0][1];
    if (H<S && H<E) {
        std::cout << 0 << ',' << 0 << '\n';
        sum += H+1;
    }
    // northeast corner
    H = (int)out[0][n];
    S = (int)out[1][n];
    W = (int)out[0][n-1];
    if (H<S && H<W) {
        std::cout << 0 << ',' << n << '\n';
        sum += H+1;
    }
    // southwest corner
    H = (int)out[m][0];
    N = (int)out[m-1][0];
    E = (int)out[m][1];
    if (H<N && H<E) {
        std::cout << m << ',' << 0 << '\n';
        sum += H+1;
    }
    // southeast corner
    H = (int)out[m][n];
    N = (int)out[m-1][n];
    W = (int)out[m][n-1];
    if (H<N && H<W) {
        std::cout << m << ',' << n << '\n';
        sum += H+1;
    }

    // 9483 too high
    // 9780 too high
    std::cout << sum << " solution1" << std::endl;
}

template<typename T>
void Sol09<T>::Solution2() {
    std::cout << " solution2" << std::endl;
}

}
