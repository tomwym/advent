#pragma once

//#include "../Base.hpp"

namespace advent21 {

template<typename T>
class Sol04 : public Base<T> {
public:
    Sol04(const std::string&);
    void Solution1();
    void Solution2();
private:
    std::vector<std::vector<T>> obj;
};


template<typename T>
Sol04<T>::Sol04(const std::string& nums)
: Base<T>(nums) { }

template<typename T>
void Sol04<T>::Solution1() {
    obj = Base<T>::ReadVVT(this->prefix + this->nums + this->suffix, ',');
    // callouts vector from first line of dat
    std::vector<T> callouts = obj[0];

    // make copy of obj from 3rd line (ind 2) to end
    std::vector<std::vector<std::string>> out;
    std::copy(this->obj.begin()+2, this->obj.end(), std::back_inserter(out));
    
    Base<T>::PrintVVT(out);
}

template<typename T>
void Sol04<T>::Solution2() {
    
}

}