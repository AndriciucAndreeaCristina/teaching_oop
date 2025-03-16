#include <iostream>

class Operator {
    int value;
    public:
        // Constructor pentru conversie implicită de la int
        Operator(int value) : value(value) {}

        // Supraîncărcăm operatorul virgulă ca membru al clasei
        Operator operator,(int b) {
            return Operator(value + b); // Stocăm direct suma
        }

        // Getter pentru valoare
        int getValue() const {
            return value;
        }
};

// Supraîncărcăm operatorul unar + pentru a extrage valoarea
int operator+(const Operator& op) {
    return op.getValue();
}


int main()
{
    int a = 5, b = 7;
    int c = a + b;
    // in cazul lui d, + este operator unar, iar operatorul , (comma operator) este un operator binar (https://en.wikipedia.org/wiki/Comma_operator)
    int d = +(a, b);
    int d2 = +(Operator(a), b);
    std::cout << c << std::endl;  // c = 12
    std::cout << d << std::endl;  // d = 7
    std::cout << d2 << std::endl; // d2 = 12

    return 0;
}