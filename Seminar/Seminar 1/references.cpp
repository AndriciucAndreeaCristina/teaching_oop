/* Test reference declaration and initialization (TestReferenceDeclaration.cpp) */
#include <iostream>

int main() {
    int number = 88;          // Declare an int variable called number
    int & refNumber = number; // Declare a reference (alias) to the variable number
    // Both refNumber and number refer to the same value

    std::cout << number << std::endl;    // Print value of variable number (88)
    std::cout << refNumber << std::endl; // Print value of reference (88)

    refNumber = 99;            // Re-assign a new value to refNumber
    std::cout << refNumber << std::endl;
    std::cout << number << std::endl;    // Value of number also changes (99)

    number = 55;               // Re-assign a new value to number
    std::cout << number << std::endl;
    std::cout << refNumber << std::endl; // Value of refNumber also changes (55)
}