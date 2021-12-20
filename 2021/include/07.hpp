#pragma once

namespace advent21 {

template<typename T>
T Cost071(const std::vector<T>& out, const T at) {
    T sum = 0;
    for (const auto& i : out) {
        sum += abs(i-at);
    }
    return sum;
}

template<typename T>
T Cost072(const std::vector<T>& out, const T at) {
    T sum = 0;
    for (const auto& i : out) {
        T temp = abs(i-at);
        //std::cout <<  0.5*(temp*temp + temp) << '\n';
        sum += 0.5*(temp*temp + temp);
    }
    return sum;
}


template<typename T>
class Sol07 : public Base {
public:
    Sol07(const std::string&);
    void Solution1();
    void Solution2();
    T Day07();
private:
    std::vector<std::vector<T>> obj;
};

template<typename T>
Sol07<T>::Sol07(const std::string& nums)
: Base(nums) { }

template<typename T>
T Sol07<T>::Day07() {
    return {};
}


template<typename T>
void Sol07<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, ',');
    std::vector<T> out = obj[0];

    T min = std::numeric_limits<T>::max();
    for (T i=0; i<out.size(); i++) {
        T val = out[i];
        T cost = Cost071(out, val);
        if (cost < min) {
            min = cost;
        }
    }
    std::cout << min << " solution1" << std::endl;
}

template<typename T>
void Sol07<T>::Solution2() {
    std::vector<T> out = obj[0];

    T min = std::numeric_limits<T>::max();
    for (T i=0; i<out.size(); i++) {
        T val = out[i];
        T cost = Cost072(out, val);
        if (cost < min) {
            min = cost;
        }
    }
    std::cout << min << " solution2" << std::endl;
}

}
