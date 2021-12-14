#include "Include.hpp"
#include <memory>
#include <algorithm>
#include <typeinfo>

using namespace advent21;

template <typename T> std::string type_name();

int main(int argc, char** argv) {
    std::string nums(argv[0]);
    nums = std::string(nums.end()-2, nums.end());

    int numi = std::stoi(nums);
    std::unique_ptr<Base<void>> truer;
    switch(numi) {
        case  1 : truer = std::make_unique<Sol01<void>>(nums); break;
        case  2 : // truer = std::make_unique<Sol02<void>>(); break;
        case  3 : // truer = std::make_unique<Sol03<void>>(); break;
        case  4 : // truer = std::make_unique<Sol04<void>>(); break;
        case  5 : // truer = std::make_unique<Sol05<void>>(); break;
        case  6 : // truer = std::make_unique<Sol06<void>>(); break;
        case  7 : // truer = std::make_unique<Sol07<void>>(); break;
        case  8 : // truer = std::make_unique<Sol08<void>>(); break;
        case  9 : // truer = std::make_unique<Sol09<void>>(); break;
        case  0 : // truer = std::make_unique<Sol10<void>>(); break;
        case 11 : // truer = std::make_unique<Sol11<void>>(); break;
        case 12 : // truer = std::make_unique<Sol12<void>>(); break;
        case 13 : // truer = std::make_unique<Sol13<void>>(); break;
        case 14 : // truer = std::make_unique<Sol14<void>>(); break;
        case 15 : // truer = std::make_unique<Sol15<void>>(); break;
        case 16 : // truer = std::make_unique<Sol16<void>>(); break;
        case 17 : // truer = std::make_unique<Sol17<void>>(); break;
        case 18 : // truer = std::make_unique<Sol18<void>>(); break;
        case 19 : // truer = std::make_unique<Sol19<void>>(); break;
        case 20 : // truer = std::make_unique<Sol20<void>>(); break;
        case 21 : // truer = std::make_unique<Sol21<void>>(); break;
        case 22 : // truer = std::make_unique<Sol22<void>>(); break;
        case 23 : // truer = std::make_unique<Sol23<void>>(); break;
        case 24 : // truer = std::make_unique<Sol24<void>>(); break;
        case 25 : // truer = std::make_unique<Sol25<void>>(); break;

        default : break; //return 0;
    }

    // std::string file= std::string("./dat/" + obj + ".dat");
    // vvs out = truer->ReadFile(file);
    // Base<void>::PrintVVS(out);
    truer->Solution1();
    truer->Solution2();

    return 0;
}
