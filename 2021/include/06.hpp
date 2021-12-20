#pragma once

namespace advent21 {

template<typename T>
class Sol06 : public Base {
public:
    Sol06(const std::string&);
    void Solution1();
    void Solution2();
    T Day06(const T);
private:
    std::vector<std::vector<T>> obj;
};

template<typename T>
Sol06<T>::Sol06(const std::string& nums)
: Base(nums) { }

template<typename T>
T Sol06<T>::Day06(const T ITERATIONS) {
    std::vector<T> container(9, 0);
    // populate the container with values of input
    for (const auto& i : obj[0]) {
        container[i]++;
    }
    for (T i=0; i<ITERATIONS; i++) {
        T buffer = container[0];
        for (int i=0; i<=7; i++) {
            container[i] = container[i+1];
        }
        container[6] += buffer;
        container[8] = buffer;
    }
    // note: accumuate assumes input 0 as integer, so need to cast it to type T
    T sum = std::accumulate(container.begin(), container.end(), static_cast<T>(0));
    return sum;
}


template<typename T>
void Sol06<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, ',');
    T sum = Day06(80);
    std::cout << sum << " solution1" << std::endl;
}

template<typename T>
void Sol06<T>::Solution2() {
    T sum = Day06(256);
    std::cout << sum << " solution2" << std::endl;
}

}
