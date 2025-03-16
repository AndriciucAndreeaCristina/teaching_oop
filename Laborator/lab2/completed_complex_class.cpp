#include <iostream>

class Complex {
    int real;
    int img;

public:
    Complex(int r = 0, int i = 0) : real(r), img(i) {}
    ~Complex() {}

    int getReal() const { return real; }
    int getImg() const { return img; }

    void setReal(int r) { real = r; }
    void setImg(int i) { img = i; }

    Complex add(Complex c) {
        return Complex(real + c.real, img + c.img);
    }

    Complex operator+(Complex c) {
        return add(c);
    }

    Complex operator-(Complex c) {
        return Complex(real - c.real, img - c.img);
    }

    Complex& operator+=(const Complex& rhs) {
        real += rhs.real;
        img += rhs.img;
        return *this;
    }

    Complex& operator-=(const Complex& rhs) {
        real -= rhs.real;
        img -= rhs.img;
        return *this;
    }

    bool operator==(const Complex& rhs) {
        return (real == rhs.real) && (img == rhs.img);
    }

    bool operator!=(const Complex& rhs) {
        return !(*this == rhs);
    }

    Complex operator*(Complex c) {
        return Complex(real * c.real - img * c.img, real * c.img + img * c.real);
    }

    friend Complex operator+(const Complex& c, int value) {
        return Complex(c.real + value, c.img);
    }

    friend Complex operator+(int value, const Complex& c) {
        return Complex(c.real + value, c.img);
    }

    friend std::ostream& operator<<(std::ostream&, const Complex&);
    friend std::istream& operator>>(std::istream&, Complex&);
};

std::ostream& operator<<(std::ostream& stream, const Complex& c) {
    stream << c.real << (c.img >= 0 ? "+" : "") << "i*" << c.img;
    return stream;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    std::cout << "Enter real part: ";
    is >> c.real;
    std::cout << "Enter imaginary part: ";
    is >> c.img;
    return is;
}

void menu() {
    Complex array[10];
    int count = 0;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add element\n";
        std::cout << "2. Delete element\n";
        std::cout << "3. Show elements\n";
        std::cout << "4. Perform operations\n";
        std::cout << "0. Exit\n";
        std::cin >> choice;

        if (choice == 1) {
            if (count < 10) {
                Complex C;
                std::cin >> C;
                array[count++] = C;
                std::cout << "Added: " << C << "\n";
            } else {
                std::cout << "Array is full!\n";
            }
        }

        else if (choice == 2) {
            int index;
            std::cout << "Enter index to delete: ";
            std::cin >> index;
            if (index >= 0 && index < count) {
                for (int i = index; i < count - 1; i++) {
                    array[i] = array[i + 1];
                }
                count--;
                std::cout << "Element deleted.\n";
            } else {
                std::cout << "Invalid index.\n";
            }
        }

        else if (choice == 3) {
            for (int i = 0; i < count; i++) {
                std::cout << "Index " << i << ": " << array[i] << "\n";
            }
        }

        else if (choice == 4) {
            int subChoice;
            std::cout << "1. Add 2 elements\n";
            std::cout << "2. Subtract 2 elements\n";
            std::cout << "3. Count identical elements\n";
            std::cout << "4. Add int to Complex\n";
            std::cin >> subChoice;

            if (subChoice == 1) {
                int i, j;
                std::cout << "Enter two indices: ";
                std::cin >> i >> j;
                if (i >= 0 && j >= 0 && i < count && j < count) {
                    std::cout << "Result: " << (array[i] + array[j]) << "\n";
                } else {
                    std::cout << "Invalid indices.\n";
                }
            } else if (subChoice == 2) {
                int i, j;
                std::cout << "Enter two indices: ";
                std::cin >> i >> j;
                if (i >= 0 && j >= 0 && i < count && j < count) {
                    std::cout << "Result: " << (array[i] - array[j]) << "\n";
                } else {
                    std::cout << "Invalid indices.\n";
                }
            } else if (subChoice == 3) {
                int identicalCount = 0;
                for (int i = 0; i < count; ++i) {
                    for (int j = i + 1; j < count; ++j) {
                        if (array[i] == array[j]) {
                            identicalCount++;
                        }
                    }
                }
                std::cout << "Identical pairs: " << identicalCount << "\n";
            } else if (subChoice == 4) {
                int i, value;
                std::cout << "Enter index and integer: ";
                std::cin >> i >> value;
                if (i >= 0 && i < count) {
                    std::cout << "Result: " << (array[i] + value) << "\n";
                } else {
                    std::cout << "Invalid index.\n";
                }
            }
        }
    }
}

int main() {
    menu();
    return 0;
}
