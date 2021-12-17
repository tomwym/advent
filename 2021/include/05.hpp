#pragma once

namespace advent21 {

template<typename T>
struct Point05 {
    T x;
    T y;
    Point05();
    Point05(T, T);
};

template<typename T>
Point05<T>::Point05() : x(0), y(0) { } 

template<typename T>
Point05<T>::Point05(T _x, T _y) : x(_x), y(_y) { }

// https://stackoverflow.com/questions/3882467/defining-operator-for-a-struct
template<typename T>
bool operator<(const Point05<T>& p1, const Point05<T>& p2) {
    return std::tie(p1.x, p1.y) < std::tie(p2.x, p2.y);
}

template<typename T>
std::vector<Point05<T>> FindLineCoverage(const int part, const Point05<T>& p1, const Point05<T>& p2) {
    std::vector<Point05<T>> obj {};

    T Dx = p2.x-p1.x;
    T dx = Dx ? Dx/abs(Dx) : 0;
    T x0 = p1.x;

    T Dy = p2.y-p1.y;
    T dy = Dy ? Dy/abs(Dy) : 0;
    T y0 = p1.y;

    if (part == 1 && abs(Dy) == abs(Dx)) {
        return obj;
    }
    
    obj.push_back(p1);
    for (int i=0; i<std::max(abs(Dx), abs(Dy)); i++) {
        x0 += dx;
        y0 += dy;
        obj.push_back(Point05(x0, y0));
    }
    return obj;
}

template<typename S, typename T>
class Sol05 : public Base {
public:
    Sol05(const std::string&);
    void Solution1();
    void Solution2();
    T Day05(const int);
private:
    std::vector<std::vector<S>> obj;
};



template<typename S, typename T>
Sol05<S,T>::Sol05(const std::string& nums)
: Base(nums) { }

template<typename S, typename T>
T Sol05<S,T>::Day05(const int part) {
    std::map<Point05<T>,T> mep {};
    for (const auto& vT : obj) {
        std::vector<T> vp1 = vTFromS<T>(vT[0], ',');
        std::vector<T> vp2 = vTFromS<T>(vT[2], ',');

        Point05<T> p1(vp1[0], vp1[1]);
        Point05<T> p2(vp2[0], vp2[1]);
        std::vector<Point05<T>> Point05sAlongLine = FindLineCoverage(part, p1, p2);

        for (const auto& pt : Point05sAlongLine) {
            auto mit = mep.find(pt);
            // key already exsits
            if (mit != mep.end()) {
                mit->second++;
            } else {
                mep[pt] = 1;
            }
        }
    }

    T outcount = 0;
    for (auto it=mep.begin(); it !=  mep.end(); it++) {
        if (it->second > 1) {
            outcount++;
        }
    }
    return outcount;
}

template<typename S, typename T>
void Sol05<S,T>::Solution1() {
    obj = ReadVVT<S>(this->filename, ' ');
    T outcount = Day05(1);
    std::cout << outcount << " solution1" << std::endl;
}

template<typename S, typename T>
void Sol05<S,T>::Solution2() {
    T outcount = Day05(2);
    std::cout << outcount << " solution2" << std::endl;
}

}