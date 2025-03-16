/* Transmiterea parametrilor */

#include <iostream>
#include <ostream>

void functie(int valoare, int *pointer, int &referinta)
{
    valoare++;      // Modifică doar copia locală
    (*pointer)++;   // Modifică variabila originală prin pointer
    referinta++;    // Modifică variabila originală direct
}

int funcValoare(int x) {
    int rezultat = x * 2;
    return rezultat;  // Întoarce o copie a valorii
}

int* funcPointer() {
    int *p = new int(5);
    return p;  // Întoarce adresa unei zone alocate dinamic

    // ATENȚIE la întoarcerea adreselor variabilelor locale!
    // int x = 5;
    // return &x;  // GREȘIT! x va fi distrusă la ieșirea din funcție
}

int& funcReferinta(int &x) {
    return x;  // Întoarce o referință la parametrul primit

    // ATENȚIE la întoarcerea referințelor către variabile locale!
    // int y = 5;
    // return y;  // GREȘIT! y va fi distrusă la ieșirea din funcție
}

int main()
{
    int x = 0, y = 0, z = 0;
    functie(x, &y, z);
    // După apel: x = 0, y = 1, z = 1

    int a = 5;

    // Întoarcere prin valoare - nu poate fi lvalue
    // funcValoare(a) = 10;  // EROARE! Nu poate fi lvalue

    // Întoarcere prin pointer - poate fi lvalue prin dereferențiere
    std::cout << *funcPointer() << std::endl;
    *funcPointer() = 10;  // Corect, modifică zona alocată dinamic
                          // Deși valoarea este setată la 10, aceasta se află doar în memoria alocată dinamic
                          //  (returnată de funcPointer), iar pointerul nu este reutilizat.
                          // se rezolva daca in funcPointer pun static int *p = new int(5)
                          // static pastreaza adresa
    std::cout << funcPointer() << std::endl;  // 0x19025661aa0
    std::cout << *funcPointer() << std::endl; // 5
    // Întoarcere prin referință - poate fi lvalue direct
    funcReferinta(a) = 10;  // Corect, modifică valoarea lui a la 10
    return 0;
}
