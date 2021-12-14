#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>

namespace advent21 {

using vvs = std::vector<std::vector<std::string>>;

template<typename T>
class Base {
public:
    Base(std::string);
    vvs ReadFile(const std::string&);
    static void PrintVVS(const vvs&);
    static std::vector<T> vTFromVVS(const vvs&);

    virtual void Solution1() = 0;
    virtual void Solution2() = 0;
    virtual ~Base() {}
protected:
    const char* prefix = "./dat/";
    const char* suffix = ".dat";
    char delimiter;
    vvs obj1;
    vvs obj2;
};

template<typename T>
Base<T>::Base(std::string nums)
: delimiter(' '), obj1({}), obj2({}) {
    obj1 = ReadFile(prefix + nums + ".1" + suffix);
    obj2 = ReadFile(prefix + nums + ".2" + suffix);
}

template<typename T>
vvs Base<T>::ReadFile(const std::string& filepath) {
    std::ifstream ifs(filepath);
    if(!ifs)
    {
        std::cout << "no file" << std::endl;
    } 

    std::string lineBuffer {};

    vvs object;

    // loop through file as input stream
    while (std::getline(ifs, lineBuffer, '\n')) {
        std::stringstream lineStream(lineBuffer);
        std::string valueBuffer {};
        std::vector<std::string> line {};
        // loop through line as input stream
        while (std::getline(lineStream, valueBuffer, delimiter)) {
            line.push_back(valueBuffer);
        }
        object.push_back(line);
    }
    return object;
}

template<typename T>
void Base<T>::PrintVVS(const vvs& obj) {
    for (const auto& vs : obj) {
        for (const auto& s : vs) {
            std::cout << s << ' ';
        }
        std::cout << '\n';
    }
    return;
}

template<typename T>
std::vector<T> Base<T>::vTFromVVS(const vvs& obj) {
    std::vector<T> out {};
    std::stringstream ss;
    T buffer;
    for (const auto& vstr : obj) {
        std::copy(vstr.begin(), vstr.end(),std::ostream_iterator<std::string>(ss,"\n"));
        ss >> buffer;
        out.push_back(buffer);
    }
    return out;
}

}
