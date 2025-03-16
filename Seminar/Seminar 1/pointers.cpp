#include <iostream>
#include <typeinfo>     // Pentru typeid
#include <type_traits>  // Pentru std::is_pointer

int main() {
  int *p1, *p2, i;    // p1 și p2 sunt pointeri la int, i este un int
  int* p3, p4, j;     // p3 este pointer la int, p4 și j sunt int
  int *p5, *p6, k;    // p5 și p6 sunt pointeri la int, k este un int

  std::cout << "Tipul lui p1: " << typeid(p1).name() << std::endl;
  std::cout << "Tipul lui p2: " << typeid(p2).name() << std::endl;
  std::cout << "Tipul lui i: " << typeid(i).name() << std::endl;

  std::cout << "Tipul lui p3: " << typeid(p3).name() << std::endl;
  std::cout << "Tipul lui p4: " << typeid(p4).name() << std::endl;
  std::cout << "Tipul lui j: " << typeid(j).name() << std::endl;

  std::cout << "Tipul lui p5: " << typeid(p5).name() << std::endl;
  std::cout << "Tipul lui p6: " << typeid(p6).name() << std::endl;
  std::cout << "Tipul lui k: " << typeid(k).name() << std::endl;

  // Verificare dacă sunt pointeri folosind std::is_pointer
  std::cout << "p1 este pointer? " << std::is_pointer<decltype(p1)>::value << std::endl;
  std::cout << "p4 este pointer? " << std::is_pointer<decltype(p4)>::value << std::endl;
  std::cout << "k este pointer? " << std::is_pointer<decltype(k)>::value << std::endl;

  int number = 88;     // An int variable with a value
  int* pNumber;       // Declare a pointer variable called pNumber pointing to an int (or int pointer)
  pNumber = &number;   // Assign the address of the variable number to pointer pNumber

  int* pAnother = &number; // Declare another int pointer and init to address of the variable number

  int number_2 = 88;
  int* pNumber_2 = &number;  // Declare and assign the address of variable number to pointer pNumber (0x58cf5ffb2c)
  std::cout << pNumber_2<< std::endl;   // Print the content of the pointer variable, which contain an address (0x58cf5ffb2c)
  std::cout << *pNumber_2 << std::endl; // Print the value "pointed to" by the pointer, which is an int (88)
  *pNumber_2 = 99;            // Assign a value to where the pointer is pointed to, NOT to the pointer variable
  std::cout << *pNumber_2 << std::endl; // Print the new value "pointed to" by the pointer (99)
  std::cout << number_2 << std::endl;   // The value of variable number changes as well (99)

  int ii = 88;
  double d = 55.66;
  int* iPtr = &ii;    // int pointer pointing to an int value
  double* dPtr = &d; // double pointer pointing to a double value

  iPtr = &d;   // ERROR, cannot hold address of different type
  dPtr = &ii;   // ERROR
  iPtr = ii;    // ERROR, pointer holds address of an int, NOT int value

  int jj = 99;
  iPtr = &jj;  // You can change the address stored in a pointer

  int* nullp = 0;         // Declare an int pointer, and initialize the pointer to point to nothing
  std::cout << *nullp << std::endl;  // ERROR! STATUS_ACCESS_VIOLATION exception

  int * p = NULL;         // Also declare a NULL pointer points to nothing
  return 0;
}
