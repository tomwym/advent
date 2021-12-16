#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <unordered_map>
#include <algorithm>

namespace advent21 {

using vvs = std::vector<std::vector<std::string>>;

template<typename T>
class Base {
public:
    Base(const std::string&);
    static std::vector<std::vector<T>> ReadVVT(const std::string&, char);
    static void PrintVVT(const std::vector<std::vector<T>>&);
    static std::vector<T> vTFromVVT(const std::vector<std::vector<T>>&);

    virtual void Solution1() = 0;
    virtual void Solution2() = 0;
    virtual ~Base() {}
protected:
    const char* prefix = "./dat/";
    const char* suffix = ".dat";
    std::string nums;
    char mdelimiter = ' ';
};

template<typename T>
Base<T>::Base(const std::string& _nums)
: nums(_nums) { }

template<typename T>
std::vector<std::vector<T>> Base<T>::ReadVVT(const std::string& filepath, char _delimiter) {
    std::vector<std::vector<T>> object {};
    std::ifstream ifs(filepath);
    if(!ifs)
    {
        std::cout << "no file\t" << filepath << std::endl;
        return object;
    } 

    std::string lineBuffer {};

    // loop through file as input stream
    while (std::getline(ifs, lineBuffer, '\n')) {
        std::replace(lineBuffer.begin(), lineBuffer.end(), _delimiter, ' ');
        std::stringstream lineStream(lineBuffer);
        std::vector<T> line {};
        // loop through linestream as input stream
        T valueBuffer {};
        while (lineStream >> valueBuffer) {
            line.push_back(valueBuffer);
        }
        object.push_back(line);
    }
    ifs.close();
    std::cout << "found file\t" << filepath << std::endl;
    return object;
}

template<typename T>
void Base<T>::PrintVVT(const std::vector<std::vector<T>>& obj) {
    for (const auto& vT : obj) {
        for (const auto& t : vT) {
            std::cout << t << ' ';
        }
        std::cout << '\n';
    }
    return;
}

template<typename T>
std::vector<T> Base<T>::vTFromVVT(const std::vector<std::vector<T>>& obj) {
    std::vector<T> out {};
    std::stringstream ss;
    T buffer;
    for (const auto& vstr : obj) {
        std::copy(vstr.begin(), vstr.end(), std::ostream_iterator<std::string>(ss,"\n"));
        ss >> buffer;
        out.push_back(buffer);
    }
    return out;
}

}
