#pragma once

namespace advent21 {

template<typename S>
class Sol14 : public Base {
public:
    Sol14(const std::string&);
    void Solution1();
    void Solution2();
    template<typename T>
    T Day14(const T);
private:
    std::vector<std::vector<S>> obj;
    std::string init;
    std::map<std::string, char> rules;
};

template<typename S>
Sol14<S>::Sol14(const std::string& nums)
: Base(nums) {
    obj = ReadVVT<S>(this->filename, ' ');
    init = obj[0][0];
    for (auto it=obj.begin()+2; it!=obj.end(); it++) {
        rules[it->at(0)] = it->at(2)[0];
    }
    // for (const auto& p : rules) {
    //     std::cout << p.first << ' ' << p.second << '\n';
    // }
}

template<typename S>
template<typename T>
T Sol14<S>::Day14(const T LOOPCOUNT) {
    std::string local_init(init);
    for (T i=0; i<LOOPCOUNT; i++) {
        const size_t CONTAINER_SIZE = local_init.size();
        const size_t NEW_CONTAINER_SIZE = 2*CONTAINER_SIZE -1;
        std::string tempnew(NEW_CONTAINER_SIZE, ' ');
        size_t index=0, og_ind=0;
        for (; index < NEW_CONTAINER_SIZE-1; ++index) {
            const std::string twochar(local_init.begin()+og_ind,  local_init.begin()+og_ind+2);
            const char newchar = rules[twochar];
            tempnew[index] = *(local_init.begin()+og_ind);
            og_ind++; ++index;
            tempnew[index] = newchar;
        }
        tempnew[index] = local_init.back();
        local_init = tempnew;
    }

    // get the character counts
    std::unordered_map<char, T> charcount;
    for (const char& c : local_init) {
        charcount[c]++;
    }

    // find most and least common element
    T max = 0;
    T min = std::numeric_limits<T>::max();
    for(const auto& p : charcount) {
        if (p.second > max) {
            max = p.second;
        } 
        if (p.second < min) {
            min = p.second;
        }
    }
    T diff = max-min;
    return diff;
}

template<typename S>
void Sol14<S>::Solution1() {
    auto diff = Day14<int>(10);
    std::cout << diff << " solution1" << std::endl;
}

template<typename S>
void Sol14<S>::Solution2() {
    auto diff = Day14<unsigned long long int>(40);
    std::cout << diff << " solution2" << std::endl;
}
}