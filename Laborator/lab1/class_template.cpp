#include <iostream>

class Student{
  char* name;
  int age;
  public:
    // Definirea constructorului parametrizat
    Student(char* name, int age){
      this->name = name;
      this->age = age;
    }

    // Definirea constructorului de copiere
    Student(const Student& student){
      this->name = student.name;
      this->age = student.age;
    }

    // Definirea unei metode de afisare date
    void displayInfo() {
      std::cout << this->name << std::endl;
      std::cout << this->age << std::endl;
    }

    // Destructor
    ~Student() {
      delete name;
    }
};

int main() {
    // Daca am definit un constructor cu parametrii, constructorul default (fara parametrii) nu mai exista
    // decomentarea liniei de mai jos = eroare
    // Student s;
    // initializare corecta:
    Student s("Ionel", 19);
    // Apelarea constructorului de copiere
    Student s2(s);
    Student s3 = s;
    // Apelarea operatorului de asignare
    s3 = s2;

    s.displayInfo();

    return 0;
}


