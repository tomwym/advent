#pragma once

namespace advent21 {

template<typename S, typename T>
class Sol13 : public Base {
public:
    Sol13(const std::string&);
    void Solution1();
    void Solution2();
    std::set<typename std::pair<T,T>> Day13(const std::vector<std::string>&);
private:
    std::vector<std::vector<S>> obj;
    std::vector<std::vector<T>> coords;
    std::vector<std::string> mirror_s;
};

template<typename S, typename T>
Sol13<S,T>::Sol13(const std::string& nums)
: Base(nums) { }

template<typename S, typename T>
std::set<typename std::pair<T,T>> Sol13<S,T>::Day13(const std::vector<std::string>& mirror_) {
    // populate set with all coordinates
    std::set<std::pair<T,T>> values;
    for (const auto& crd : coords) {
        values.insert(std::make_pair(crd[0], crd[1]));
    }

    for (const auto& s : mirror_) {
        T plane = std::stoi(std::string(s.begin()+2, s.end()));

        // container to store iterators to erase and insert
        std::vector<typename std::set<std::pair<T,T>>::iterator> to_erase;
        std::vector<typename std::pair<T,T>> to_insert;

        for (const auto& p : values) {
            // if the x value is greater than plane
            if (s[0] == 'x' && p.first > plane) {
                std::pair<T,T> temp = std::make_pair(2*plane-p.first, p.second);               
                to_insert.push_back(temp);
                to_erase.push_back(values.find(p));
            }
            // otherwise its mirror accross y: if y is greater than plane
            else if (s[0] == 'y' && p.second > plane) {
                std::pair<T,T> temp = std::make_pair(p.first, 2*plane-p.second);
                to_insert.push_back(temp);
                to_erase.push_back(values.find(p));
            }
        }
        // insert keys into set 
        for (const auto& ins : to_insert) {
            values.insert(ins);
        }
        // remove keys from folded half
        for (const auto& erase : to_erase) {
            values.erase(erase);
        }
    }
    return values;
}

template<typename S, typename T>
void Sol13<S,T>::Solution1() {
    {
        auto temp = ReadVVT<T>(this->filename, ',');
        auto it = temp.begin();
        while (it->size()>1) {
            it++;
        }
        // construct vector of coordinates 
        std::copy(temp.begin(), it, std::back_inserter(coords));
        it++;
        int offset = &*it - &temp[0];
        // construct mirror planes vector
        auto temp2 = ReadVVT<S>(this->filename, ' ');
        for (auto it2=temp2.begin()+offset; it2!=temp2.end(); it2++) {
            mirror_s.push_back((*it2)[2]);
        }
    }
    // give only first instruction
    std::vector<std::string> mirror_s1 {mirror_s[0]};
    std::set<typename std::pair<T,T>> values = Day13(mirror_s1);

    std::cout << values.size() << " solution1" << std::endl;
}

template<typename S, typename T>
void Sol13<S,T>::Solution2() {
    std::set<typename std::pair<T,T>> values = Day13(mirror_s);

    T maxx = std::numeric_limits<T>::min();
    T maxy = std::numeric_limits<T>::min();
    // find max width and height
    for (const auto& pr : values) {
        if (pr.first > maxx) {
            maxx = pr.first;
        }
        if (pr.second > maxy) {
            maxy = pr.second;
        }
    }
    // create canvas
    std::vector<std::string> ACSII(maxy+1, std::string(maxx+1, '.'));

    for (const auto& pr : values) {
        ACSII[pr.second][pr.first] = '#';
    }
    for (const auto& s : ACSII) {
        std::cout << s << '\n';
    }

    std::cout << "solution2" << std::endl;
}

}
