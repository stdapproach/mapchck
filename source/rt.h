#ifndef RT_H
#define RT_H

namespace mapchck {
namespace rt {
//+Irreflexivity  f(x, x) must be false.
//+Antisymmetry  f(x, y) implies !f(y, x)
//Transitivity  f(x, y) and f(y, z) imply f(x, z).
//Transitivity of equivalence  Equivalence (as defined above) is transitive: if x is equivalent
//to y and y is equivalent to z, then x is equivalent to z. (This implies that equivalence does
//in fact satisfy the mathematical definition of an equivalence relation.) [1]


//check Irreflexivity  f(x, x) must be false.
template <typename T>inline
bool checkIrreflexivity(const T& obj1) {return (obj1 < obj1);}

//Antisymmetry  f(x, y) implies !f(y, x)
template <typename T>inline
bool checkAntisymmetry(const T& lh, const T& rh) {
    bool a1 = (lh < rh);
    bool a2 = (rh < lh);
    return (a1 != a2);
}

//Transitivity  f(x, y) and f(y, z) imply f(x, z).
template <typename T>inline
bool checkTransitivity(const T& a, const T& b, const T& c) {
    bool f1 = (a < b);
    bool f2 = (b < c);
    bool f3 = (a < c);
    //return (f1 && f2) == f3;
    if (f1 && f2) {
        return f3;
    }
    if (!f1 && !f2) {
        return !f3;
    }
    return (f1 || f2) == f3;
    //return (f1 ^ f2) ==f3;
    //return ((f1 || f2) && !(f1 && f2))==f3;
}

}
}

#endif // RT_H
