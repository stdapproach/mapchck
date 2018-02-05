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

template <typename T>inline
void tstIrreflexivityVec(const std::initializer_list<T>&vt, bool referenceResult) {
    std::cout << "Check Irreflexivity.." << std::endl;
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
    for(auto it1 = vt.begin(); it1 != vt.end(); ++it1) {
        int j{i};
        for(auto it2 = it1; it2 != vt.end(); ++it2) {
            if(it2 != it1) {
                auto lh = *it1;
                auto rh = *it2;
                auto a = rt::checkAntisymmetry(lh, rh);
                std::cout <<
                             ((referenceResult == a)? "  ok for: "
                             :"!! Antisymmetry been broken for: ")
                          << "[i=" << i << ",j=" << j << "] "
                          << typeid(*it1).name()
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
    for(auto it1 = vt.begin(); it1 != vt.end(); ++it1) {
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
                              <<5//<< typeid(*it1).name()
                              << "(" << a.i << b.i<< c.i<<std::endl;
                }
                ++k;
            }
            ++j;
        }
        ++i;
    }
}

template<typename T>inline
std::initializer_list<T> hlprGenerator() {
    return {T(), T(1), T(2)};
}

void run() {
    std::cout<<"start run-time checking for map/set correctness"<<std::endl;

    auto foo0 = hlprGenerator<Foo0>();
    auto foo1 = hlprGenerator<Foo1_IrreflexivityBroken>();
    //tstIrreflexivityVec(foo0, false);
    //tstIrreflexivityVec(foo1, false);
    //
    //tstAntisymmetryVec(foo0, true);
    //tstAntisymmetryVec(foo1, true);
    auto foo2 = hlprGenerator<Foo2_AntisymmetryBroken>();
    //tstAntisymmetryVec(foo2, true);
    //
    auto a = rt::checkTransitivity(Foo0(1), Foo0(0), Foo0(2));
    //tstTransitivityVec(foo0, true);
    //auto a = rt::checkTransitivity(Foo0(), Foo0(1), Foo0(2));
//    auto a = rt::checkTransitivity(Foo1_IrreflexivityBroken(),
//                                   Foo1_IrreflexivityBroken(1),
//                                   Foo1_IrreflexivityBroken());
    std::cout << "a=" << a << std::endl;
}


}
}

#endif // TST_RTCHCK_H
