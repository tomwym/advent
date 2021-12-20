#pragma once

namespace advent21 {

template<typename T>
class Sol01 : public Base {
public:
    Sol01(std::string);
    void Solution1();
    void Solution2();
private:
    std::vector<std::vector<T>> obj;
};


template<typename T>
Sol01<T>::Sol01(std::string nums)
: Base(nums) { }

template<typename T>
void Sol01<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, ',');
    std::vector<T> out = vTFromVVT<T>(obj);
    int increases = 0;
    for (size_t i=0; i<out.size()-1; i++) {
        increases += (out[i+1] - out[i]) > 0;
    }
    std::cout << increases << " solution1" << std::endl;
}

template<typename T>
void Sol01<T>::Solution2() {
    std::vector<T> out = vTFromVVT<T>(obj);
    int increases = 0;
    for (size_t i=1; i<out.size()-2; i++) {
        int first = out[i-1] + out[i] + out[i+1];
        int second = out[i] + out[i+1] + out[i+2];
        increases += (second - first) > 0;
    }
    std::cout << increases << " solution2" << std::endl;
}

}
