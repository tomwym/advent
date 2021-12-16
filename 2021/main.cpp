#include "Include.hpp"
#include <memory>
#include <algorithm>
#include <typeinfo>

using namespace advent21;

template <typename T> std::string type_name();

int main(int argc, char** argv) {
    std::string nums(argv[1]);
    nums = std::string(nums.end()-2, nums.end());

    int numi = std::stoi(nums);
    std::unique_ptr<Base> truer;
    switch(numi) {
        case  1 : truer = std::make_unique<Sol01<int>>(nums); break;
        case  2 : truer = std::make_unique<Sol02<std::string>>(nums); break;
        case  3 : truer = std::make_unique<Sol03<std::string>>(nums); break;
        case  4 : truer = std::make_unique<Sol04<int>>(nums); break;
        case  5 : // truer = std::make_unique<Sol05<void>>(nums); break;
        case  6 : // truer = std::make_unique<Sol06<void>>(nums); break;
        case  7 : // truer = std::make_unique<Sol07<void>>(nums); break;
        case  8 : // truer = std::make_unique<Sol08<void>>(nums); break;
        case  9 : // truer = std::make_unique<Sol09<void>>(nums); break;
        case  0 : // truer = std::make_unique<Sol10<void>>(nums); break;
        case 11 : // truer = std::make_unique<Sol11<void>>(nums); break;
        case 12 : // truer = std::make_unique<Sol12<void>>(nums); break;
        case 13 : // truer = std::make_unique<Sol13<void>>(nums); break;
        case 14 : // truer = std::make_unique<Sol14<void>>(nums); break;
        case 15 : // truer = std::make_unique<Sol15<void>>(nums); break;
        case 16 : // truer = std::make_unique<Sol16<void>>(nums); break;
        case 17 : // truer = std::make_unique<Sol17<void>>(nums); break;
        case 18 : // truer = std::make_unique<Sol18<void>>(nums); break;
        case 19 : // truer = std::make_unique<Sol19<void>>(nums); break;
        case 20 : // truer = std::make_unique<Sol20<void>>(nums); break;
        case 21 : // truer = std::make_unique<Sol21<void>>(nums); break;
        case 22 : // truer = std::make_unique<Sol22<void>>(nums); break;
        case 23 : // truer = std::make_unique<Sol23<void>>(nums); break;
        case 24 : // truer = std::make_unique<Sol24<void>>(nums); break;
        case 25 : // truer = std::make_unique<Sol25<void>>(nums); break;

        default : break; //return 0;
    }
    std::cout << "Day " << nums << '\n';
    truer->Solution1();
    std::cout << std::endl;
    truer->Solution2();
    std::cout << "***** ***** ***** ***** *****" << '\n' << std::endl;
    return 0;
}
