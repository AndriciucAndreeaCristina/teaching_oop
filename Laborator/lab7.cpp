#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(const string& name, int age) : name(name), age(age) {}
    virtual void displayInfo() const = 0;
    virtual ~Person() = default;
};

class Teacher : virtual public Person {
protected:
    string subject;

public:
    Teacher(const string& name, int age, const string& subject)
        : Person(name, age), subject(subject) {}

    void displayInfo() const override {
        cout << "\n[Teacher Info]\n";
        cout << "Name: " << name << "\nAge: " << age << "\nSubject: " << subject << "\n";
    }
};

class Administrator : virtual public Person {
protected:
    string department;
public:
    Administrator(const string& name, int age, const string& department)
        : Person(name, age), department(department) {}

    void displayInfo() const override {
        cout << "\n[Administrator Info]\n";
        cout << "Name: " << name << "\nAge: " << age << "\nDepartment: " << department << "\n";
    }
};

class HeadOfDepartment : public Teacher, public Administrator {
    int experience;
public:
    HeadOfDepartment(const string& name, int age,
                     const string& subject, const string& department, int experience)
        : Person(name, age),
          Teacher(name, age, subject),
          Administrator(name, age, department),
          experience(experience) {}

    void displayInfo() const override {
        cout << "\n[Head of Department Info]\n";
        cout << "Name: " << name << "\nAge: " << age
             << "\nSubject: " << subject
             << "\nDepartment: " << department
             << "\nYears of Experience as HoD: " << experience << "\n";
    }
};

int main() {
    vector<Person*> staff;

    staff.push_back(new Teacher("Paun Andrei", 50, "POO"));
    staff.push_back(new Administrator("Bogdan Alexe", 43, "Admitere"));
    staff.push_back(new HeadOfDepartment("Alin Stefanescu", 50, "MDS", "INFO", 8));

    for (Person* p : staff) {
        p->displayInfo();
    }

    for (Person* p : staff) {
        delete p;
    }

    return 0;
}
