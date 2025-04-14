/****
 * 1. Definiti o clasa de baza din care sa se mosteneasca o clasa derivata (alocare dinamica)
 * 2. Aruncati/Provocati exceptii in constructor si destructor. Ce se intampla?
 * 3. Faceti in main o succesiune de catch-uri pt int, char*, Base&, Derived&
 * 4. Faceti exception-handeling pt input gresit
 ****/

#include <iostream>

using namespace std;

class Base
{
    int* array_base;
    int value;
public:
    Base(int value=10) : value(value)
    {
        cout << "Base constructor" << endl;
        try
        {
            array_base = new int[value];
        }
        catch (bad_alloc& e)
        {
            cout<<"Exception in constructor base: "<<e.what()<<endl;
        }
    }
    virtual ~Base()
    {
        try
        {
            cout<<"Base Destructor"<<endl;
            throw 17;       // un throw in destructor nu părăsește destructorul, de aceea avem try-catch aici.
            delete[] array_base;
        }
        catch (int error)
        {
            cout<<"Exception in destructor: "<<error<<endl;
        }

    }
    int getValue()
    {
        return value;
    }
};

class Derived : public Base
{
    int value_derived;
    int* array_derived;
public:
    Derived(int value_derived) : Base(), value_derived(value_derived)
    {
        cout << "Derived constructor" << endl;
        try
        {
            array_derived = new int[value_derived];
        }
        catch (bad_alloc& e)
        {
            cout<<"Exception in constructor derived: "<<e.what()<<endl;
        }
    }
    ~Derived()
    {
        try
        {
            cout<<"Derived Destructor"<<endl;
            throw "Error in destructor derived";
            delete[] array_derived;
        }
        catch (const char* message)
        {
            cout << message << endl;
        }
    }
    operator int()
    {
        return value_derived;
    }
};

int citesteInt() {
    int x;
    cout << "Introdu un numar: ";
    cin >> x;
    if (cin.fail()) {
        cin.clear(); // resetăm flag-ul de eroare
        cin.ignore(1000, '\n'); // curățăm bufferul
        throw runtime_error("Input invalid! Introdu un numar intreg.");
    }
    return x;
}

int main()
{
    Base* base_ptr =nullptr;
    try
    {
        //Base* base = new Base(1000000000000000);
        //Derived base_cast = *static_cast<Derived*>(new Base(1000000000000000));
        Derived* obj = new Derived(10);
        base_ptr = dynamic_cast<Derived*>(obj);
        delete base_ptr;  // nu putem sa facem handle la exceptii din destructori
    }
    catch (int error)
    {
        cout<<error<<endl;
    }
    catch (const char* message)
    {
        cout << message << endl;
    }
    catch (Derived& d)
    {
        cout<<"Exception of d"<<endl;
    }
    catch (bad_alloc& e)
    {
        cout<<e.what()<<endl;
    }
    cout<<"Outside try-catch block 1\n";

    try {
        // Test 1: aruncăm o excepție int
        //throw 42;

        // Test 2: aruncăm un mesaj
        //throw "Eroare de test";

        // Test 3: aruncam obiect Derived
        Derived obj2 = *new Derived(10);
        //throw obj2;  // ajunge in catch de derivata
        Derived* obj3 = new Derived(10);
        //throw obj3;   // ajunge in catch(...)
        Base obj4 = *new Derived(10);
        //throw obj4;  // ajunge in catch de baza
        Derived* obj5 = dynamic_cast<Derived*>(new Base(10));
        //throw *obj5; // segmentation fault, dereferentiem nullptr si nu se poate!!!

    }

    catch (int e) {
        cout << "Catch int: " << e << endl;
    }

    catch (const char* msg) {      // daca las doar char*, throw-ul ”Eroare de test” va fi prins in catch(...)
        cout << "Catch char*: " << msg << endl;
    }

    catch (Derived& d) {
        cout << "Catch Derived&\n";
    }

    catch (Base& b) {
        cout << "Catch Base&\n";
    }

    catch (...) {
        cout << "Catch all\n";
    }

    int valoare;
    while (true)
        try {
            valoare = citesteInt();
            cout << "Ai introdus: " << valoare << endl;
            break;
        } catch (const exception& e) {
            cout << "Exceptie la input: " << e.what() << endl;
        }
    cout<<"In final, valoarea introdusa este: "<<valoare<<endl;
    return 0;
}