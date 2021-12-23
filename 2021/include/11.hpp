#pragma once

namespace advent21 {

const int SIZE = 10;

template<typename T>
class Coord11{
public:
    T i;
    T j;
    Coord11(T _i, T _j) : i(_i), j(_j) {}
    // https://stackoverflow.com/questions/4660123/overloading-friend-operator-for-template-class
    template<typename Y>
    friend std::ostream& operator<<(std::ostream& os, const Coord11<Y>& coord);
};

template<typename Y>
std::ostream& operator<<(std::ostream& os, const Coord11<Y>& coord) {
    os << '(' << coord.i << ',' << coord.j << ')';
    return os;
}

template<typename T>
T P2L(const Coord11<T>& coord) {
    return SIZE*coord.i + coord.j;
}

template<typename T>
Coord11<T> L2P(const T linear) {
    T j = linear % SIZE;
    T i = (linear-j) / SIZE;
    return Coord11(i, j);
}

template<typename T>
std::vector<Coord11<T>> getRing(T i, T j) {
    std::vector<Coord11<T>> out {};
    // check via row major directions 
    if (i>0) {
        // NW
        if (j > 0) {
            out.push_back(Coord11<T>(i-1,j-1));
        }
        // N
        out.push_back(Coord11<T>(i-1,j));
        // NE
        if (j < SIZE-1) {
            out.push_back(Coord11<T>(i-1,j+1));
        }        
    }
    // W
    if (j > 0) {
        out.push_back(Coord11<T>(i,j-1));
    }    
    // E
    if (j < SIZE-1) {
        out.push_back(Coord11<T>(i,j+1));
    }
    if (i < SIZE-1) {
        // SW
        if (j > 0) {
            out.push_back(Coord11<T>(i+1,j-1));
        }
        // S
        out.push_back(Coord11<T>(i+1,j));        
        // SE
        if (j < SIZE-1) {
            out.push_back(Coord11<T>(i+1,j+1));
        }
    }

    return out;
}

// consider (i,j) == (1,1)
template<typename T> 
void look(const T i, const T j, T& flashcount,
       std::array<std::array<T, SIZE>, SIZE>& container,
       std::vector<bool>& hasFlashed) {
    T location = P2L<T>(Coord11<T>(i,j));
    if (hasFlashed[location]) {
        return;
    }
    container[i][j]++;
    if (container[i][j] == 10) {
        hasFlashed[location] = true;
        container[i][j] = 0;
        flashcount++;
        std::vector<Coord11<T>> looknext = getRing(i,j);
        for (const auto& coord : looknext) {
            look(coord.i, coord.j, flashcount, container, hasFlashed);
        }
    }
}

template<typename T>
bool totalSum(const std::array<std::array<T, SIZE>, SIZE>& container) {
    T sum = 0;
    for (const auto& ar : container) {
        sum += std::accumulate(ar.begin(), ar.end(), static_cast<T>(0));
    }
    return sum;
}

template<typename S, typename T>
class Sol11 : public Base {
public:
    Sol11(const std::string&);
    void Solution1();
    void Solution2();
    T Day11(const int);
private:
    std::vector<std::vector<S>> obj;
    std::array<std::array<T, SIZE>, SIZE> m_container;
};

template<typename S, typename T>
Sol11<S,T>::Sol11(const std::string& nums)
: Base(nums) { }

template<typename S, typename T>
T Sol11<S,T>::Day11(const int part) {
    return {};
}

template<typename S, typename T>
void Sol11<S,T>::Solution1() {
    obj = ReadVVT<S>(this->filename, ' ');
    std::vector<S> vS = vTFromVVT<S>(obj);
    // populate the container first
    for (size_t i=0; i<SIZE; i++) {
        for (size_t j=0; j<SIZE; j++) {
            m_container[i][j] = vS[i][j]-'0';
        }
    }
    std::array<std::array<T, SIZE>, SIZE> container(m_container);

    T flashcount = 0;
    const int STEPS = 100;
    for (int s=0; s<STEPS; s++) {
        std::vector<bool> hasFlashed (SIZE*SIZE, false);
        std::vector<T> listB {};
        for (size_t i=0; i<SIZE; i++) {
            for (size_t j=0; j<SIZE; j++) {
                look<T>(i, j, flashcount, container, hasFlashed);
            }
        }
    }

    std::cout << flashcount << " solution1" << std::endl;
}

template<typename S, typename T>
void Sol11<S,T>::Solution2() {
    std::array<std::array<T, SIZE>, SIZE> container(m_container);
    T flashcount = 0;
    T iterations = 0;
    while (totalSum(container)) {
        std::vector<bool> hasFlashed (SIZE*SIZE, false);
        std::vector<T> listB {};
        for (size_t i=0; i<SIZE; i++) {
            for (size_t j=0; j<SIZE; j++) {
                look<T>(i, j, flashcount, container, hasFlashed);
            }
        }
        iterations++;
    }

    std::cout << iterations << " solution2" << std::endl;
}

}
