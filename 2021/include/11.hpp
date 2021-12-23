#pragma once

namespace advent21 {

const int SIZE = 10;

template<typename T>
struct Coord11{
    T i;
    T j;
    Coord11(T _i, T _j) : i(_i), j(_j) {}
};

template<typename T>
T P2L(const Coord11<T>& coord) {
    return SIZE*coord.i + coord.j;
}

template<typename T>
Coord11<T> L2P(const T linear) {
    T j = linear % SIZE;
    T i = (linear-j) / SIZE;
    return Coord11(i, j);
}

template<typename S, typename T>
class Sol11 : public Base {
public:
    Sol11(const std::string&);
    void Solution1();
    void Solution2();
    T Day11(const int);
private:
    std::vector<std::vector<S>> obj;
};



template<typename S, typename T>
Sol11<S,T>::Sol11(const std::string& nums)
: Base(nums) { }

template<typename S, typename T>
T Sol11<S,T>::Day11(const int part) {
    return {};
}

template<typename S, typename T>
void Sol11<S,T>::Solution1() {
    obj = ReadVVT<S>(this->filename, ' ');
    std::vector<S> vS = vTFromVVT<S>(obj);
    std::array<std::array<T, SIZE>, SIZE> container {};
    for (size_t i=0; i<SIZE; i++) {
        for (size_t j=0; j<SIZE; j++) {
            container[i][j] = std::stoi(std::string({vS[i][j]}));
        }
    }

    for (const auto& row : container) {
        for (const auto& i : row) {
            std::cout << i;
        }
        std::cout << '\n';
    }

    const int STEPS = 2;
    for (int i=0; i<STEPS; i++) {

    }
    std::cout << " solution1" << std::endl;
}

template<typename S, typename T>
void Sol11<S,T>::Solution2() {
    std::cout << " solution2" << std::endl;
}

}
