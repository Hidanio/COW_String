#include <iostream>
#include "Cow_str.h"
int main() {
    CowString A = CowString("abc");
    CowString B = A;



    std::cout << A << '\n';
    B[0] = 'd';
    std::cout << B << '\n';
    std::cout << A << '\n';
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
