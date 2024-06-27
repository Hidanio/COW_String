#include <iostream>
#include "Cow_str.h"

int main() {
// Create and testing basic CowString
    CowString cowString("hello");
    cowString.debug(); // Should be "hello" with 1 ref

// Copy str
    auto cowS = cowString;
    cowS.debug(); // Should be "hello" with 2 refs
    cowString.debug(); // Also 2 refs

// Modify of copy str
    cowS[1] = 'x';
    std::cout << "After modification:\n";
    cowS.debug(); // Should be "hxello" with 1 ref
    cowString.debug(); // Should be "hello" with 1 ref

// Concatenation
    CowString concatenated = cowString + " world";
    std::cout << "Concatenated string: " << concatenated << std::endl;

//  substr
    CowString substring = cowString.substr(1, 3);
    std::cout << "Substring: " << substring << std::endl;

// Work with StringWrapper
    std::cout << "===========================\n";
    StringWrapper str("world");
    str.debug(); // "world"
    std::cout << "StringWrapper data: " << str.getData() << std::endl;

    return 0;
}
