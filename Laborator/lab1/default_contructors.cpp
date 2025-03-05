

class Student{
};

int main() {
    // Instanțierea clasei Student, se apelează constructorul fără parametrii
    Student s;

    // Apelarea constructorului de copiere
    Student s2(s);
    Student s3 = s;

    // Apelarea constructorului fără parametrii
    Student s4;

    // Apelarea operatorului de atribuire
    s4 = s2;

    // Apelarea destructorului in ordinea inversă a definirii
    // Se apelează destructorul pentru s4
    // Se apelează destructorul pentru s3
    // Se apelează destructorul pentru s2
    // Se apelează destructorul pentru s1
}


