#include <iostream>

int main()
{
    int* a = new int;    // aloca memorie pentru un int si pastreaza adresa in a
    int* b = new int;    // aloca memorie pentru un int si pastreaza adresa in b

    std::cin>>*a;        // citeste valoarea si o stocheaza la adresa de memorie indicata de a
    std::cin>>*b;         // citeste valoarea si o stocheaza la adresa de memorie indicata de b

    std::cout<<*a + *b<<std::endl; // afiseaza suma

    // mai avem de eliberat memorie
    // un good practice este sa ne asiguram ca exista ceva la adresa de memorie de unde vrem sa stergem
    if (b)
    {
        delete b;
        b = nullptr;
    }

    // pentru un exemplu simplu cum este acesta, acceptam si varianta fara verificare
    delete a;
    a = nullptr;
    return 0;
}