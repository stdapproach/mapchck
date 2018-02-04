#ifndef RT_H
#define RT_H

namespace mapchck {
namespace rt {

namespace hlpr {
//check Irreflexivity  f(x, x) must be false.
template <typename T>inline
bool checkIrreflexivity(const T& obj1) {return (obj1 < obj1);}

//Antisymmetry  f(x, y) implies !f(y, x)

}
}
}

#endif // RT_H
