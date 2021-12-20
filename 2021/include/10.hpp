#pragma once

namespace advent21 {

template<typename T>
class Sol10 : public Base {
public:
    Sol10(const std::string&);
    void Solution1();
    void Solution2();
    T Day10();
private:
    std::vector<std::vector<T>> obj;
};

template<typename T>
Sol10<T>::Sol10(const std::string& nums)
: Base(nums) { }

template<typename T>
T Sol10<T>::Day10() {
    return {};
}


template<typename T>
void Sol10<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, ',');
    std::vector<std::string> vS = vTFromVVT(obj);
    std::string test1 = vS[0];
    // general rule: new char must either be an opening bracket
    // or a closing bracket which closes the current top char
    // otherwise it's an invalid string
    std::unordered_map<char, char> pears = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    std::unordered_map<char, int> cost = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    std::stack<char> container;
    int sum = 0;
    for (const auto& s : vS) {
        for (const auto& c : s) {
            // opening bracket
            if (c=='(' || c=='[' || c=='{' || c=='<') {
                container.push(c);
            }
            else if (c == pears[container.top()]) {
                container.pop();
            } else {
                sum += cost[c];
                break;
            }
        }
    }

    std::cout << sum << " solution1" << std::endl;
}

template<typename T>
void Sol10<T>::Solution2() {
    std::cout << " solution2" << std::endl;
}

}
