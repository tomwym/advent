#pragma once

namespace advent21 {

template<typename T>
class Sol02 : public Base {
public:
    Sol02(std::string);
    void Solution1();
    void Solution2();
private:
    std::vector<std::vector<T>> obj;
};


template<typename T>
Sol02<T>::Sol02(std::string nums)
: Base(nums) { }

template<typename T>
void Sol02<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, ',');
    std::stringstream ss;
    std::string key {};
    int increment = 0;
    int depth = 0;
    int range = 0;
    for(const auto& vstr : obj ) {
        std::copy(vstr.begin(), vstr.end(), 
                  std::ostream_iterator<std::string>(ss,"\n"));
        ss >> key >> increment;
        if (key == "forward") {
            range += increment;
        } else if (key == "down") {
            depth += increment;
        } else if (key == "up") {
            depth -= increment;
        }
    }
    std::cout << depth << '\t' << range << '\n';
    std::cout << depth*range << " solution1" << std::endl;
}

template<typename T>
void Sol02<T>::Solution2() {
    std::stringstream ss;
    std::string key {};
    int increment = 0;
    int aim = 0;
    int depth = 0;
    int range = 0;
    for(const auto& vstr : obj ) {
        std::copy(vstr.begin(), vstr.end(), 
                  std::ostream_iterator<std::string>(ss,"\n"));
        ss >> key >> increment;
        if (key == "forward") {
            range += increment;
            depth += aim*increment;
        } else if (key == "down") {
            aim += increment;
        } else if (key == "up") {
            aim -= increment;
        }
    }
    std::cout << depth << '\t' << range << '\n';
    std::cout << depth*range << " solution2" << std::endl;
}

}