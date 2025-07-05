#include <iostream>

// Para habilitar/deshabilitar partes de los Ejemplos
#define _CONSTRUCTORS_      0
#define _MEMBER_INIT_LIST_  0
#define _DESTRUCTORS_       1

    #if _CONSTRUCTORS_
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
    #endif  //#if _CONSTRUCTORS_

    #if _MEMBER_INIT_LIST_
// Lista de Inicializadores de Miembros (Member Initializer List)
class Rectangulo {
public:
    int ancho;
    int alto;

    // Constructor parametrizado usando lista de inicializadores de miembros
    Rectangulo(int a, int b) : ancho(a), alto(b) {
        std::cout << "Constructor parametrizado (con lista de inicializadores) llamado." << std::endl;
    }
    // NOTA: Para un constructor por defecto, puedes usar {} si no hay lógica extra
    // Rectangulo() : ancho(0), alto(0) {}
    Rectangulo() : ancho(0), alto(0) {
        std::cout << "Constructor por defecto llamado." << std::endl;
    }

    int getArea() {
        return ancho * alto;
    }
};
    #endif  //#if _MEMBER_INIT_LIST_

    #if _DESTRUCTORS_
class Rectangulo {
public:
    int ancho;
    int alto;
    int* datosExtras; // Un puntero para simular memoria dinámica

    Rectangulo(int a, int b) : ancho(a), alto(b) {
        datosExtras = new int[10]; // Simulamos asignación de memoria
        std::cout << "Constructor llamado. Memoria asignada para datosExtras." << std::endl;
    }

    // El Destructor
    // Se llama cuando el objeto es destruido (sale del scope, delete, etc.)
    ~Rectangulo() {
        delete[] datosExtras; // Liberar la memoria asignada
        std::cout << "Destructor llamado. Memoria de datosExtras liberada." << std::endl;
    }
};
    #endif  //#if _DESTRUCTORS_

int main() {

        #if _CONSTRUCTORS_
    Rectangulo r1;
    std::cout << "r1.getArea() = " << r1.getArea() << std::endl;
    Rectangulo r2(10, 20);  // Llama al constructor parametrizado
    std::cout << "r2.getArea() = " << r2.getArea() << std::endl;
    Rectangulo r3(5);       // Llama al constructor para un cuadrado
    std::cout << "r3.getArea() = " << r3.getArea() << std::endl;
    std::cout << "(c)2025 VRX Desing" << std::endl;
        #endif  //#if _CONSTRUCTORS_

        #if _MEMBER_INIT_LIST_
    Rectangulo r1(12,15);
    std::cout << "r1.getArea() = " << r1.getArea() << std::endl;
    Rectangulo r2;
    std::cout << "r2.getArea() = " << r2.getArea() << std::endl;
        #endif  //#if _MEMBER_INIT_LIST_
    
        #if _DESTRUCTORS_
     // Objeto en el stack (memoria automática)
    Rectangulo r1(10, 20); // Constructor llamado
    // ... r1 existe y es usable ...
    // Cuando main termina, r1 sale de scope y su destructor se llama automáticamente.

    std::cout << "--- Creando objeto din""\xA0""micamente ---" << std::endl;

    // Objeto en el heap (memoria dinámica)
    Rectangulo* r_ptr = new Rectangulo(30, 40); // Constructor llamado
    // ... *r_ptr existe y es usable ...
    delete r_ptr; // Debemos llamar explícitamente 'delete' para que el destructor se llame
                  // y la memoria asignada sea liberada.
                  // ¡Si olvidas 'delete', tendrás una fuga de memoria!

    std::cout << "Fin del programa." << std::endl;
        #endif  //#if _CONSTRUCTORS_

    return 0;
}