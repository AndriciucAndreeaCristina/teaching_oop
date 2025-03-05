#include <iostream>
#include <cstring> 

class Car {
private:
    char brand[20]{};
    char model[20]{};
    int year;

public:
    Car(const char* b, const char* m, int y) {
        strcpy(brand, b);
        strcpy(model, m);
        year = y;
    }

    const char *getBrand() const {
        return brand;
    }

    const char *getModel() const {
        return model;
    }

    int getYear() const {
        return year;
    }

    void setBrand(const char* b) {
        strcpy(brand, b);
    }

    void setModel(const char* m) {
        strcpy(model, m);
    }

    void setYear(int y) {
        year = y;
    }

    void displayInfo() const {
        std::cout << "Car: " << brand << " " << model << " (" << year << ")" << std::endl;
    }
};

int main() {
    Car myCar("Toyota", "Corolla", 2020);

    myCar.displayInfo();

    myCar.setYear(2022);
    std::cout << "Updated year: " << myCar.getYear() << std::endl;

    return 0;
}
