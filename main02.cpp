#include <iostream>

class Rectangulo {
public:
    int ancho;
    int alto;

    // 1. Constructor por Defecto (Default Constructor)
    // Se llama cuando haces Rectangulo r;
    Rectangulo() {
        ancho = 0;
        alto = 0;
        std::cout << "Constructor por defecto llamado." << std::endl;
    }

    // 2. Constructor Parametrizado (Parameterized Constructor)
    // Se llama cuando haces Rectangulo r(10, 20);
    Rectangulo(int a, int b) {
        ancho = a;
        alto = b;
        std::cout << "Constructor parametrizado (int, int) llamado." << std::endl;
    }

    // 3. Constructor parametrizado sobrecargado (overloaded Parameterized Constructor)
    Rectangulo(int lado) {
        ancho = lado;
        alto = lado;
        std::cout << "Constructor parametrizado (int) llamado (cuadrado)." << std::endl;
    }

    int getArea() {
        return ancho * alto;
    }
};

// Uso:
// Rectangulo r1;           // Llama al constructor por defecto
// Rectangulo r2(10, 20);   // Llama al constructor parametrizado
// Rectangulo r3(5);        // Llama al constructor para un cuadrado

int main() {
    Rectangulo r1;
    std::cout << "r1.getArea() = " << r1.getArea() << std::endl;
    Rectangulo r2(10, 20);  // Llama al constructor parametrizado
    std::cout << "r2.getArea() = " << r2.getArea() << std::endl;
    Rectangulo r3(5);       // Llama al constructor para un cuadrado
    std::cout << "r3.getArea() = " << r3.getArea() << std::endl;
}