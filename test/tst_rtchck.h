#ifndef TST_RTCHCK_H
#define TST_RTCHCK_H

#include <initializer_list>
#include <iostream>
#include <typeinfo>


#include "../source/rt.h"

namespace mapchck {
namespace tst_rt {

struct Foo0 {
    int i;
    //Foo0():i(0){}
    Foo0(int vi=0):i(vi){}
    bool operator< (const Foo0&lh) const{return this->i < lh.i;}
};

struct Foo1_IrreflexivityBroken {
    int i;
    Foo1_IrreflexivityBroken(int vi=0):i(vi){}
    bool operator< (const Foo1_IrreflexivityBroken&lh) const{return this->i <= lh.i;}
};

struct Foo2_AntisymmetryBroken {
    int i;
    Foo2_AntisymmetryBroken(int vi=0):i(vi){}
    bool operator< (const Foo2_AntisymmetryBroken&lh) const{return false;}
};

struct Foo3_TransitivityBroken {
    int i;
    Foo3_TransitivityBroken(int vi):i(vi){}
    bool operator< (const Foo3_TransitivityBroken&lh) const
    {
        if (this->i == 0 && lh.i == 2)
            return false;
        else
            return this->i < lh.i;
    }
};

template <typename T>inline
void tstIrreflexivityVec(const std::initializer_list<T>&vt, bool referenceResult) {
    std::cout << "Check Irreflexivity for.." << std::endl;
    int i{0};
    for(auto it1: vt) {
        auto a = rt::checkIrreflexivity(it1);
        std::cout <<
                     ((referenceResult == a)? "  ok for: "
                     :"!! Irreflexivity been broken for: ")
                  << "[i=" << i << "] "
                  << typeid(it1).name()
                  << std::endl;
        ++i;
    }
}

template <typename T>inline
void tstAntisymmetryVec(const std::initializer_list<T>&vt, bool referenceResult) {
    std::cout << "Check Antisymmetry.." << std::endl;
    int i{0};
    for(auto it1 = begin(vt); it1 != end(vt); ++it1) {
        int j{i};
        for(auto it2 = it1; it2 != end(vt); ++it2) {
            if(it2 != it1) {
                auto lh = *it1;
                auto rh = *it2;
                auto a = rt::checkAntisymmetry(lh, rh);
                std::cout <<
                             ((referenceResult == a)? "  ok for: "
                             :"!! Antisymmetry been broken for: ")
                          << "[i=" << i << ",j=" << j << "] "
                          << typeid(lh).name()
                          << std::endl;
            }
            ++j;
        }
        ++i;
    }
}

template <typename T>inline
void tstTransitivityVec(const std::initializer_list<T>&vt, bool referenceResult) {
    std::cout << "Check Transitivity.." << std::endl;
    int i{0};
    for(auto it1 = begin(vt); it1 != end(vt); ++it1) {
        int j{0};
        for(auto it2 = begin(vt); it2 != end(vt); ++it2) {
            int k{0};
            for(auto it3 = begin(vt); it3 != end(vt); ++it3) {
                if(i!=j && i!=k && j!=k)
                {
                    auto a = *it1;
                    auto b = *it2;
                    auto c = *it3;
                    auto res = rt::checkTransitivity(a, b, c);
                    std::cout <<
                                 ((referenceResult == res)? "  ok for: "
                                 :"!! Transitivity been broken for: ")
                              << "[i=" << i << ",j=" << j << ",k=" << k << "]"
                              << typeid(a).name()
                              <<std::endl;
                }
                ++k;
            }
            ++j;
        }
        ++i;
    }
}

void run() {
    std::cout<<"start run-time checking for map/set correctness"<<std::endl;

    const auto foo0 = {Foo0(0),
                       Foo0(1),
                       Foo0(2)};

    const auto foo1 = {Foo1_IrreflexivityBroken(0),
                       Foo1_IrreflexivityBroken(1),
                       Foo1_IrreflexivityBroken(2)};

    const auto foo2 = {Foo2_AntisymmetryBroken(0),
                       Foo2_AntisymmetryBroken(1),
                       Foo2_AntisymmetryBroken(2)};

    const auto foo3 = {Foo3_TransitivityBroken(0),
                       Foo3_TransitivityBroken(1),
                       Foo3_TransitivityBroken(2)};

    const bool doCheckIrreflexivity = true;
    if(doCheckIrreflexivity) {
        tstIrreflexivityVec(foo0, false);
        tstIrreflexivityVec(foo1, false);
    }

    const bool doCheckAntisymmetry = true;
    if (doCheckAntisymmetry) {
        tstAntisymmetryVec(foo0, true);
        tstAntisymmetryVec(foo1, true);
        tstAntisymmetryVec(foo2, true);
    }

    const bool doCheckTransitivity = true;
    if (doCheckTransitivity) {
        tstTransitivityVec(foo0, true);
        tstTransitivityVec(foo1, true);
        tstTransitivityVec(foo2, true);
        tstTransitivityVec(foo3, true);
    }
}


}
}

#endif // TST_RTCHCK_H
