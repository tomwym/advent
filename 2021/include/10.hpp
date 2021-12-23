#pragma once

namespace advent21 {

template<typename S, typename T>
class Sol10 : public Base {
public:
    Sol10(const std::string&);
    void Solution1();
    void Solution2();
    T Day10();
private:
    std::vector<std::vector<S>> obj;
};

template<typename S, typename T>
Sol10<S,T>::Sol10(const std::string& nums)
: Base(nums) { }

template<typename S, typename T>
T Sol10<S,T>::Day10() {
    return {};
}


template<typename S, typename T>
void Sol10<S,T>::Solution1() {
    obj = ReadVVT<S>(this->filename, ',');
    std::vector<S> vS = vTFromVVT<S>(obj);
    // general rule: new char must either be an opening bracket
    // or a closing bracket which closes the current top char
    // otherwise it's an invalid string
    std::unordered_map<char, char> pears = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    std::unordered_map<char, T> cost = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    T sum = 0;
    for (const auto& s : vS) {
        std::stack<char> container;
        for (const auto& c : s) {
            // opening bracket
            if (c=='(' || c=='[' || c=='{' || c=='<') {
                container.push(c);
            }
            // must close the top if not opening
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

template<typename S, typename T>
void Sol10<S,T>::Solution2() {
    std::vector<S> vS = vTFromVVT<S>(obj);
    std::vector<T> score = {};
    std::unordered_map<char, char> pears = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    std::unordered_map<char, T> cost = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
    for (const auto& s : vS) {
        std::stack<char> container;
        bool valid = true;
        for (const auto& c : s) {
            // opening bracket
            if (c=='(' || c=='[' || c=='{' || c=='<') {
                container.push(c);
            }
            // must close the top if not opening
            else if (c == pears[container.top()]) {
                container.pop();
            } else {
                valid = false;
                break;
            }
        }
        T sum = 0;
        if (valid) {
            while (!container.empty()) {
                sum = 5*sum + cost[pears[container.top()]]; 
                container.pop();
            }
            std::cout << sum << '\n';
            score.push_back(sum);
        }
    }
    std::sort(score.begin(), score.end());
    T out = score[score.size()/2];

    std::cout << out << " solution2" << std::endl;
}

}

/*
[({([[{{
({[<{(
{([(<{}[<S,T>[]}>{[]{[(<()>
((((<{<{{
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
<{[{[{{[[
[<(<(<(<{}))><([]([]()
<{([([[(<S,T>()){}]>(<<{{
<{([

*/