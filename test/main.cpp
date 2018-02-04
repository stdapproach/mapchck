#include <iostream>

#include "tst_rtchck.h"

using namespace std;
using namespace mapchck;

//Irreflexivity  f(x, x) must be false.
//Antisymmetry  f(x, y) implies !f(y, x)
//Transitivity  f(x, y) and f(y, z) imply f(x, z).
//Transitivity of equivalence  Equivalence (as defined above) is transitive: if x is equivalent
//to y and y is equivalent to z, then x is equivalent to z. (This implies that equivalence does
//in fact satisfy the mathematical definition of an equivalence relation.) [1]


int main()
{
    cout << "Hello World!" << endl;
    tst_rt::func2();
    return 0;
}
