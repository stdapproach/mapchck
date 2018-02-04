#ifndef TST_RTCHCK_H
#define TST_RTCHCK_H

#include <iostream>
#include <typeinfo>

#include "../source/rt.h"

namespace mapchck {
namespace tst_rt {

struct Foo0 {
    int i;
    Foo0():i(0){}
    bool operator< (const Foo0&lh) const{return this->i < lh.i;}
};

struct Foo1_IrreflexivityBroken {
    int i;
    Foo1_IrreflexivityBroken():i(0){}
    bool operator< (const Foo1_IrreflexivityBroken&lh) const{return this->i <= lh.i;}
};

template <typename T>inline
void tstIrreflexivity(const T&t, bool referenceResult) {
    std::cout << "Check checkIrreflexivity.." << std::endl;
    auto a = rt::hlpr::checkIrreflexivity(t);
    std::cout <<
                 ((referenceResult == a)? "  ok for: "
                 :"!! Irreflexivity been broken for: ")
              << typeid(t).name()
              << std::endl;
}


void func2() {
    std::cout<<"func2"<<std::endl;

    tstIrreflexivity(Foo0(), false);
    tstIrreflexivity(Foo1_IrreflexivityBroken(), true);
}


}
}

#endif // TST_RTCHCK_H
