#include <iostream>

// Para habilitar/deshabilitar partes de los Ejemplos
#define _CLASSES_       0
#define _INHERITANCE_   0
#define _IOSTREAM_      0
#define _STRING_        0
#define _REFS_          0
#define _NEW_           0
#define _OVERLOAD_      0
#define _TEMPLATES_     0
#define _CMAKE_         1

#if _STRING_ || _CMAKE_
#include <string> // Necesario para std::string
#endif  //#if _STRING_ || _CMAKE_

// Tabla de equivalencia Code Page 437
// 'á' '\xA0' 'é' '\x82' 'í' '\xA1'
// 'ó' '\xA2' 'ú' '\xA3'
// 'ñ' '\xA4' 'Ñ' '\xA5'

#if _CLASSES_ || _INHERITANCE_
// Ejemplo en C:
// struct Persona {
//     char nombre[50];
//     int edad;
// };

// Equivalente en C++ (Clase):
class Persona {
public: // Especificador de acceso
    // Atributos
    std::string nombre; // Usamos std::string en lugar de char[]
    int edad;

    // Métodos (funciones miembro)
    void saludar() {
        std::cout << "Hola, mi nombre es " << nombre << " y tengo " << edad << " años." << std::endl;
    }

    // Constructor (función especial para inicializar objetos)
    Persona(std::string n, int e) : nombre(n), edad(e) {}
};

// Para crear un objeto:
// Persona p1; // En C
// p1.edad = 30;

#endif  //#if _CLASSES_ || _INHERITANCE_

#if _INHERITANCE_
class Estudiante : public Persona { // Estudiante hereda de Persona
public:
    std::string carrera;

    Estudiante(std::string n, int e, std::string c) : Persona(n, e), carrera(c) {}

    void estudiar() {
        std::cout << nombre << " está estudiando " << carrera << "." << std::endl;
    }
};
#endif  //#if _INHERITANCE_

#if _OVERLOAD_
void imprimir(int i) { std::cout << "Entero: " << i << std::endl; }
void imprimir(double d) { std::cout << "Double: " << d << std::endl; }
void imprimir(const std::string& s) { std::cout << "String: " << s << std::endl; }
#endif  //#if _OVERLOAD_

#if _TEMPLATES_
template <typename T>
T maximo(T a, T b) {
    return (a > b) ? a : b;
}
#endif  //#if _TEMPLATES_

// En C++:
int main() {
    #if _CLASSES_
    Persona p1("Ana", 30); // Llama al constructor
    p1.saludar(); // Llama a un método
    #endif  //#if _CLASSES_

    #if _INHERITANCE_
    Estudiante e1("Ana", 30, "Economía"); // Llama al constructor
    e1.estudiar(); // Llama a un método
    #endif  //#if _INHERITANCE_

    #if _IOSTREAM_
    int numero;
    std::cout << "Ingresa un número: "; // Salida
    std::cin >> numero; // Entrada
    std::cout << "El número ingresado es: " << numero << std::endl; // std::endl para nueva línea y vaciar buffer
    #endif  //#if _IOSTREAM_

    #if _STRING_
    std::string saludo = "Hola mundo";
    std::string nombre = "C++";
    std::string mensaje = saludo + ", " + nombre + "!"; // Concatenación sencilla

    std::cout << mensaje << std::endl;
    std::cout << "Longitud del mensaje: " << mensaje.length() << std::endl;
    #endif  //#if _STRING_

    #if _REFS_
    int a = 10;
    int* ptr = &a; // Puntero a 'a'
    int& ref = a;  // Referencia a 'a'

    std::cout << "Valor de a: " << a << std::endl;
    std::cout << "Valor a través del puntero: " << *ptr << std::endl;
    std::cout << "Valor a través de la referencia: " << ref << std::endl;

    ref = 20; // Cambia el valor de 'a'
    std::cout << "Nuevo valor de a: " << a << std::endl;
    #endif  //#if _REFS_

    #if _NEW_
    int* pEntero = new int; // Asigna memoria para un entero
    *pEntero = 100;
    std::cout << "Valor dinámico *pEntero: " << *pEntero << std::endl;
    delete pEntero; // Libera la memoria

    // Para arrays
    int* pArray = new int[5]; // Asigna memoria para un array de 5 enteros
    for (int i=0;i<5;i++) {
        pArray[i] = 100*(i+1);
        std::cout << pArray[i] << std::endl;
    }
    std::cout << "Valor dinámico *pArray: " << sizeof(*pArray) << std::endl;
    delete[] pArray; // Libera la memoria del array
    #endif  //#if _NEW_

    #if _OVERLOAD_
    imprimir(1234);
    imprimir(1.234f);
    imprimir("1234");
    #endif  //#if _OVERLOAD_

    #if _TEMPLATES_
    int m_int = maximo(5, 10);
    double m_double = maximo(3.14, 2.71);
    std::cout << "Entero: " << m_int << std::endl;
    std::cout << "Double: " << m_double << std::endl;
    #endif  //#if _TEMPLATES_

    #if _CMAKE_
    std::string build_type;

    #ifdef NDEBUG
    // NDEBUG se define típicamente en modo Release
    build_type = "Release";
    #else
    // Si NDEBUG no está definido, asumimos Debug (o Debug como defecto)
    build_type = "Debug";
    #endif

    std::cout << "\xAD""Hola desde C++!" << std::endl;
    std::cout << "Este programa fue compilado en modo: " << build_type << std::endl;
    #endif    //#if _CMAKE_

    return 0;
}
