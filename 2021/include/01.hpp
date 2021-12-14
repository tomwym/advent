#pragma once

//#include "../Base.hpp"

namespace advent21 {

template<typename T>
class Sol01 : public Base<T> {
public:
    Sol01(std::string);
    void Solution1();
    void Solution2();
};


template<typename T>
Sol01<T>::Sol01(std::string nums)
: Base<T>(nums) { }

template<typename T>
void Sol01<T>::Solution1() {
    std::vector<int> out = Base<int>::vTFromVVS(this->obj1);
    int increases = 0;
    for (int i=0; i<out.size()-1; i++) {
        increases += (out[i+1] - out[i]) > 0;
    }
    std::cout << increases << " solution1" << std::endl;
}

template<typename T>
void Sol01<T>::Solution2() {
    std::vector<int> out = Base<int>::vTFromVVS(this->obj2);
    int increases = 0;
    for (int i=1; i<out.size()-2; i++) {
        int first = out[i-1] + out[i] + out[i+1];
        int second = out[i] + out[i+1] + out[i+2];
        increases += (second - first) > 0;
    }
    std::cout << increases << " solution2" << std::endl;
}

}