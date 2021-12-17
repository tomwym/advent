#pragma once

namespace advent21 {

const int NUM_BINGO_ELEMENTS = 25;

template<typename T> 
bool CheckBingo(std::array<bool, NUM_BINGO_ELEMENTS> card){
    // go throw each 'row' of the card, returning true if any row is filled
    for (int i=0; i<=NUM_BINGO_ELEMENTS-5; i+=5) {
        bool ans = true;
        for (int j=i; j<i+5; j++) {
            if (!card[j]) {
                ans = false;
                break;
            }
        }
        if (ans) {
            return true;
        }
    }

    // do the same for each column
    for (int i=0; i<5; i++) {
        bool ans = true;
        for (int j=i; j<=i+NUM_BINGO_ELEMENTS-5; j+=5) {
            if (!card[j]) {
                ans = false;
                break;
            }
        }
        if (ans) {
            return true;
        }
    }
    return false;
}

template<typename T>
int FindSumUnmarked(std::array<bool, NUM_BINGO_ELEMENTS> card, 
                    std::array<T, NUM_BINGO_ELEMENTS> cardVals) {
    int i = 0;
    T sum = 0;
    for (const auto& truth : card) {
        i = &truth - &card[0];
        if (!truth) {
            sum += cardVals[i];
        }
    }
    return sum;
}

template<typename T>
class Sol04 : public Base {
public:
    Sol04(const std::string&);
    void Solution1();
    void Solution2();
private:
    std::vector<std::vector<T>> obj;
    std::vector<T> callouts;
    std::vector<std::array<T, NUM_BINGO_ELEMENTS>> bingocards;
};


template<typename T>
Sol04<T>::Sol04(const std::string& nums)
: Base(nums) { }

template<typename T>
void Sol04<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, ',');
    // callouts vector from first line of dat
    callouts = obj[0];

    // copy data into vector of arrays (bingocards)
    for (auto it = obj.begin()+1; it != obj.end(); ) {
        int k = 0;
        std::array<T, NUM_BINGO_ELEMENTS> temp;
        it++;
        for (int j=0; j<5; j++, it++, k+=5) {
            // i = it - obj.begin()+1;
            std::copy(it->begin(), it->end(), temp.begin()+k);
        }

        bingocards.push_back(temp);

    }

    // populate vector of bool arrays representing if value is checked
    std::array<bool, NUM_BINGO_ELEMENTS> _temp;
    _temp.fill(false);
    std::vector<std::array<bool, NUM_BINGO_ELEMENTS>> ifbingos(bingocards.size(), _temp);

    // containers for found values
    int sumOfUnmarked = 0;
    int calloutWhenDONE = 0;
    int boardind = 0;

    int calloutnum = 0;
    // iterate through list of callouts
    for (const auto& call : callouts) {
        calloutnum = &call - &callouts[0];
        // std::cout << call << ' ';
        // iterate through list of bingo cards to check if there are any matching values
        int i = 0; // i to keep track of which card

        for (const auto& card : bingocards) {
            // i is card index
            i = &card - &bingocards[0];

            int j = 0;
            // iterate through card itself
            for (const auto& square : card) {
                // j is value index in card
                j = &square - &card[0];
                if (call == square) {
                    ifbingos[i][j] = true;
                }
            }
            if (CheckBingo<void>(ifbingos[i])) {
                boardind = i;
                sumOfUnmarked = FindSumUnmarked<T>(ifbingos[i], card);
                calloutWhenDONE = call;
                goto DONE1;
            }
        }
    }
    DONE1: 
    std::cout << calloutnum << ' ' << boardind << ' ' << sumOfUnmarked << ' ' << calloutWhenDONE << '\n';
    std::cout << sumOfUnmarked * calloutWhenDONE << " solution1" << std::endl;
}

template<typename T>
void Sol04<T>::Solution2() {
    // populate vector of bool arrays representing if value is checked
    std::array<bool, NUM_BINGO_ELEMENTS> _temp;
    _temp.fill(false);
    std::vector<std::array<bool, NUM_BINGO_ELEMENTS>> ifbingos(bingocards.size(), _temp);

    // containers for found values
    int sumOfUnmarked = 0;
    int calloutWhenDONE = 0;
    int boardind = 0;

    // keep track of which cards are full/aren't
    std::vector<bool> allCardsFilled(bingocards.size(), false);
    std::vector<bool> allTrue(bingocards.size(), true); // used to compare to later

    int calloutnum = 0;
    // iterate through list of callouts
    for (const auto& call : callouts) {
        calloutnum = &call - &callouts[0];
        // std::cout << call << ' ';
        // iterate through list of bingo cards to check if there are any matching values
        int i = 0; // i to keep track of which card
        for (const auto& card : bingocards) {
            // i is card index
            i = &card - &bingocards[0];

            int j = 0;
            // iterate through card itself
            for (const auto& square : card) {
                // j is value index in card
                j = &square - &card[0];
                if (call == square) {
                    ifbingos[i][j] = true;
                }
            }
            if (!allCardsFilled[i] && CheckBingo<void>(ifbingos[i])) {
                allCardsFilled[i] = true;
                if (allCardsFilled == allTrue) {;
                    boardind = i;
                    sumOfUnmarked = FindSumUnmarked<T>(ifbingos[i], card);
                    calloutWhenDONE = call;
                    goto DONE2;
                }
            }
        }
    }
    DONE2:
    std::cout << calloutnum << ' ' << boardind << ' ' << sumOfUnmarked << ' ' << calloutWhenDONE << '\n';
    std::cout << sumOfUnmarked * calloutWhenDONE << " solution2" << std::endl;
}

}