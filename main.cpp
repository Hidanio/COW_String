#include <iostream>
#include "Cow_str.h"
int main() {
/*    CowString A = CowString("abc");
    CowString B = A;



    std::cout << A << '\n';
    B[0] = 'd';
    std::cout << B << '\n';
    std::cout << A << '\n';
    std::cout << "Hello, World!" << std::endl;*/

    CowString cowString("hello");
    cowString.debug();
    auto cowS = cowString;
    cowS[1] = 'x';
    std::cout << "==========================="<<"\n";
    StringWrapper str("world");
    str.debug();
    str.printData();
    return 0;
}
