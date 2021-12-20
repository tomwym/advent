#pragma once

namespace advent21 {

bool doesContain(const std::string& lookIn, const std::string& lookFor) {
    for (const auto& c : lookFor) {
        if (lookIn.find(c) == std::string::npos) { 
            return false;
        }
    }
    return true;
}

// compare two strings as sets
bool almostEqual(std::string str1, std::string str2) {
    std::sort(str1.begin(), str1.end());
    std::sort(str2.begin(), str2.end());
    return str1 == str2;
}

template<typename T>
class Sol08 : public Base {
public:
    Sol08(const std::string&);
    void Solution1();
    void Solution2();
    T Day08();
private:
    std::vector<std::vector<T>> obj;
};

template<typename T>
Sol08<T>::Sol08(const std::string& nums)
: Base(nums) { }

template<typename T>
T Sol08<T>::Day08() {
    return {};
}


template<typename T>
void Sol08<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, ',');
    int count = 0;
    for (const auto& vS : obj) {
        for (auto it=vS.begin()+11; it != vS.end(); it++) {
            size_t sz = it->size();
            // 1 4 7 8
            if (sz == 2 || sz == 4 || sz == 3 || sz == 7) {
                count++;
            }
        }
    }
    std::cout << count << " solution1" << std::endl;
}

template<typename T>
void Sol08<T>::Solution2() {
    int out = 0;

    for (const auto& vS : obj) {
        // map of segment strings, key values being the represented integer
        std::map<int, std::string> mep {};
        // set of found strings
        std::set<std::string> sat {};
        int index = &vS - &obj[0];
        // first loop through to determine the important keys (1,4,7,8)
        for (auto it=vS.begin(); it != vS.begin()+10; it++) {
            size_t sz = it->size();
            // 1 4 7 8
            if (sz == 2) {
                mep[1] = *it; // std::vector<char>(it->begin(), it->end());
                sat.insert(*it);
            } else if (sz == 4) {
                mep[4] = *it;
                sat.insert(*it);
            } else if (sz == 3) {
                mep[7] = *it;
                sat.insert(*it);
            } else if (sz == 7) {
                mep[8] = *it;
                sat.insert(*it);
            }
        }

        // try to find
        std::vector<std::string> look256 {};
        std::vector<std::string> look390 {};

        for (auto it=vS.begin(); it != vS.begin()+10; it++) {
            size_t sz = it->size();
            // do nothing if it's a value we know already
            if (sz == 2 || sz == 4 || sz == 3 || sz == 7) {
            } else {
                if (!doesContain(*it, mep[1])) {
                    look256.push_back(*it);
                } else if (doesContain(*it, mep[7])) {
                    look390.push_back(*it);
                }
            }
        }
        // determine 2, 5, 6
        // scan through all values index 0-9 and
        // look for components that dont have segments belonging to 1
        // 2 contains one segment of 1, and 1 contains the other segment
        // determine which is the 2 (five, six) and which is the 1 (two)
        // also set six because its the only string in 256 with size of 6
        std::vector<std::string> one0 {};
        std::vector<std::string> one1 {};
        for (const auto& s : look256) {
            if (s.size() == 6) {
                mep[6] = s;
                sat.insert(s);
            }
            if (doesContain(s, std::string({mep[1][0]}))) {
                one0.push_back(s);
            } else {
                one1.push_back(s);
            }
        }
        // (five, six) are associated with the first char of one (mep[1][0])
        if (one0.size() > one1.size()) {
            for (const auto& s : one0) {
                if (sat.find(s) == sat.end()) {
                    // this should only insert mep[5]
                    mep[5] = s;
                    sat.insert(s);
                }
            }
            mep[2] = one1[0];
            sat.insert(one1[0]);
        } 
        // the alternative is (fix, six) are associated with mep[1][1]
        else {
            for (const auto& s : one1) {
                if (sat.find(s) == sat.end()) {
                    // this should only insert mep[5]
                    mep[5] = s;
                    sat.insert(s);
                }
            }
            mep[2] = one0[0];
            sat.insert(one0[0]);
        }
        
        // now do the same for 3, 9, 0
        for (const auto& s : look390) {
            if (s.size() == 5) {
                mep[3] = s;
                sat.insert(s);
            } else if (doesContain(s, std::string({mep[4]}))) {
                mep[9] = s;
                sat.insert(s);
            } else {
                mep[0] = s;
                sat.insert(s);
            }
        }
        // put it all together
        std::string number {};
        for (auto it=vS.begin()+11; it != vS.end(); it++) {
            for (const auto& pear : mep) {
                if (almostEqual(pear.second, *it)) {
                    number += std::to_string(pear.first);
                }
            }
        }
        std::cout << index << ' ' << number << '\n';
        out += std::stoi(number);

    }
    std::cout << out << " solution2" << std::endl;
}

}