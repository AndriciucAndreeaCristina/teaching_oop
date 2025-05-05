#include <iostream>
#include <string>

using namespace std;

// Clasa de bază generică
template <typename T>
class TemplateBase {
public:
    virtual void info() const = 0;  // metodă virtuală pură
    virtual ~TemplateBase() = default;
};

// ------------------ ANIMAL ------------------------

template <typename T>
class Animal : public TemplateBase<T> {
protected:
    string name;
public:
    Animal(const string& name) : name(name) {}
    virtual void makeSound() const = 0;
};

class Cat : public Animal<string> {
public:
    Cat(const string& name) : Animal(name) {}

    void makeSound() const override {
        cout << name << " spune: Miau!" << endl;
    }

    void info() const override {
        cout << "Pisica: " << name << endl;
    }
};

class Dog : public Animal<string> {
public:
    Dog(const string& name) : Animal(name) {}

    void makeSound() const override {
        cout << name << " spune: Ham!" << endl;
    }

    void info() const override {
        cout << "Câine: " << name << endl;
    }
};

// ------------------ SHAPE ------------------------

template <typename T>
class Shape : public TemplateBase<T> {
public:
    virtual T area() const = 0;
};

class Circle : public Shape<double> {
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }

    void info() const override {
        cout << "Cerc cu rază " << radius << ", aria: " << area() << endl;
    }
};

class Triangle : public Shape<double> {
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}

    double area() const override {
        return 0.5 * base * height;
    }

    void info() const override {
        cout << "Triunghi cu bază " << base << " și înălțime " << height
             << ", aria: " << area() << endl;
    }
};

// ------------------ MAIN ------------------------

int main() {
    Cat c("Luna");
    Dog d("Max");

    Circle circ(5.0);
    Triangle tri(3.0, 4.0);

    // Polimorfism pe bază de template
    TemplateBase<string>* animal1 = &c;
    TemplateBase<string>* animal2 = &d;
    TemplateBase<double>* shape1 = &circ;
    TemplateBase<double>* shape2 = &tri;

    // Apeluri pentru info() (polimorfism)
    animal1->info();
    animal2->info();
    shape1->info();
    shape2->info();

    // Apeluri specifice
    c.makeSound();
    d.makeSound();

    // Folosim dynamic_cast pentru a verifica tipul real al obiectului la runtime
    cout << "\nVerificare cu dynamic_cast:\n";

    // dynamic_cast pentru Animal
    if (Cat* catPtr = dynamic_cast<Cat*>(animal1)) {
        cout << "animal1 este un obiect de tipul Cat.\n";
        catPtr->makeSound();
    } else if (Dog* dogPtr = dynamic_cast<Dog*>(animal1)) {
        cout << "animal1 este un obiect de tipul Dog.\n";
        dogPtr->makeSound();
    }

    if (Cat* catPtr = dynamic_cast<Cat*>(animal2)) {
        cout << "animal2 este un obiect de tipul Cat.\n";
        catPtr->makeSound();
    } else if (Dog* dogPtr = dynamic_cast<Dog*>(animal2)) {
        cout << "animal2 este un obiect de tipul Dog.\n";
        dogPtr->makeSound();
    }

    // Casturi pentru Shape
    if (Circle* circlePtr = dynamic_cast<Circle*>(shape1)) {
        cout << "shape1 este un obiect de tipul Circle.\n";
        cout << "Aria cercului este: " << circlePtr->area() << endl;
    }

    if (Triangle* trianglePtr = dynamic_cast<Triangle*>(shape2)) {
        cout << "shape2 este un obiect de tipul Triangle.\n";
        cout << "Aria triunghiului este: " << trianglePtr->area() << endl;
    }

    // ------------------ STATIC_CAST ------------------------

    // static_cast - conversii între tipuri compatibile
    cout << "\nVerificare cu static_cast:\n";

    // Convertim Animal* la Cat* (acesta este un cast sigur deoarece animal1 pointează la un obiect de tipul Cat)
    Cat* catPtr = static_cast<Cat*>(animal1);
    catPtr->makeSound();  // Vom apela makeSound pentru catPtr

    // static_cast pentru conversie între tipuri fundamentale
    double radius = static_cast<double>(5);  // conversie de la int la double
    cout << "Rația cercului este: " << radius << endl;

    // ------------------ REINTERPRET_CAST ------------------------

    // reinterpret_cast - folosit pentru a forța un cast între tipuri complet diferite
    cout << "\nVerificare cu reinterpret_cast:\n";

    // Creăm un pointer la un obiect de tip Animal și îl reinterpretăm ca fiind un pointer la un obiect de tip Circle
    Circle* circleReinterpret = reinterpret_cast<Circle*>(animal1);
    // NOTĂ: Acest cast nu este sigur, deoarece animal1 pointează de fapt către un obiect de tipul Cat, nu un Circle.
    // Vom obține un comportament imprevizibil, dar este o demonstrație de ce trebuie să fim foarte atenți cu reinterpret_cast.
    // circleReinterpret->area();  // Acesta poate duce la un comportament neașteptat!

    // ------------------ CONST_CAST ------------------------

    // const_cast - modificăm un obiect constant
    cout << "\nVerificare cu const_cast:\n";

    const string constantName = "Luna";
    const string* ptrConst = &constantName;

    // Încercăm să modificăm pointerul la un obiect constant
    string* nonConstPtr = const_cast<string*>(ptrConst);
    *nonConstPtr = "Max";  // Modificăm valoarea, chiar dacă ptrConst era constant.

    cout << "Noul nume este: " << constantName << endl;  // Afișează "Max"

    return 0;
}
