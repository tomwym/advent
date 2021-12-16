#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <unordered_map>
#include <numeric>
#include <algorithm>

namespace advent21 {

using vvs = std::vector<std::vector<std::string>>;

class Base {
public:
    Base(const std::string&);
    // static std::vector<std::vector<T>> ReadVVT(const std::string&, char);
    // static void PrintVVT(const std::vector<std::vector<T>>&);
    // static std::vector<T> vTFromVVT(const std::vector<std::vector<T>>&);

    virtual void Solution1() = 0;
    virtual void Solution2() = 0;
    virtual ~Base() {}
protected:
    const char* prefix = "./dat/";
    const char* suffix = ".dat";
    std::string filename;
    //std::string nums;
    char mdelimiter = ' ';
};

Base::Base(const std::string& _nums)
: filename(prefix + _nums + suffix) { }

template<typename T>
std::vector<std::vector<T>> ReadVVT(const std::string& filepath, char _delimiter) {
    std::vector<std::vector<T>> object {};
    std::ifstream ifs(filepath);
    if(!ifs)
    {
        std::cout << "No file\t" << filepath << std::endl;
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
    std::cout << "Found file\t" << filepath << std::endl;
    return object;
}

template<typename T>
void PrintVVT(const std::vector<std::vector<T>>& obj) {
    for (const auto& vT : obj) {
        for (const auto& t : vT) {
            std::cout << t << ' ';
        }
        std::cout << '\n';
    }
    return;
}

template<typename T>
std::vector<T> vTFromVVT(const std::vector<std::vector<T>>& obj) {
    std::vector<T> out {};
    T buffer;
    for (const auto& vT : obj) {
        // std::copy(vstr.begin(), vstr.end(), std::ostream_iterator<std::string>(ss,"\n"));
        out.push_back(vT[0]);
        // ss >> buffer;
        // out.push_back(buffer);
    }
    return out;
}

}
