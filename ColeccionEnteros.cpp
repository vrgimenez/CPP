#define _CTOR_AND_DTOR_         0
#define _COPY_CONSTRUCTOR_      0
#define _COPY_ASSIGNMENT_OPE_   1

#include <iostream> // Para std::cout y std::endl
    #if _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_
#include <algorithm> // For std::copy
    #endif

class ColeccionEnteros {
private:
    int* datos;     // Puntero al array de enteros en el heap
    int tamano;     // Tamaño actual de la colección

public:
        #if _CTOR_AND_DTOR_ || _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_
    // --- Constructores ---

    // 1. Constructor por Defecto (Default Constructor)
    // Inicializa una colección vacía.
    ColeccionEnteros() : datos(nullptr), tamano(0) {
        std::cout << "DEBUG: Constructor por defecto de ColeccionEnteros llamado (vacía)." << std::endl;
    }

    // 2. Constructor Parametrizado (Parametrized Constructor)
    // Crea una colección de un tamaño dado y asigna memoria.
    ColeccionEnteros(int n) : tamano(n) {
        if (tamano > 0) {
            datos = new int[tamano]; // Asignación de memoria en el heap
            std::cout << "DEBUG: Constructor parametrizado de ColeccionEnteros llamado. Memoria asignada para "
                      << tamano << " elementos." << std::endl;
            // Opcional: inicializar los elementos a 0
            for (int i = 0; i < tamano; ++i) {
                datos[i] = 0;
            }
        } else {
            datos = nullptr;
            tamano = 0;
            std::cout << "DEBUG: Constructor parametrizado de ColeccionEnteros llamado con tamaño no válido o cero." << std::endl;
        }
    }

    // --- Destructor ---
    // Libera la memoria asignada cuando el objeto es destruido.
    ~ColeccionEnteros() {
        if (datos != nullptr) {
            delete[] datos; // Liberar el array de memoria
            datos = nullptr; // Buenas prácticas: evitar punteros colgantes
            std::cout << "DEBUG: Destructor de ColeccionEnteros llamado. Memoria de "
                      << tamano << " elementos liberada." << std::endl;
        } else {
            std::cout << "DEBUG: Destructor de ColeccionEnteros llamado. No había memoria que liberar." << std::endl;
        }
    }
        #endif  //#if _CTOR_AND_DTOR_ || _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_

        #if _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_
    // --- Copy Constructor ---
    // Takes a const reference to another object of the same class.
    // Creates a deep copy of the source object's data.
    ColeccionEnteros(const ColeccionEnteros& other) : tamano(other.tamano) {
        std::cout << "DEBUG: Copy Constructor called." << std::endl;
        if (tamano > 0) {
            datos = new int[tamano]; // 1. Allocate NEW memory
            std::copy(other.datos, other.datos + tamano, datos); // 2. Deep copy the data
        } else {
            datos = nullptr;
        }
    }
        #endif  //#if _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_

        #if _COPY_ASSIGNMENT_OPE_
    // --- Copy Assignment Operator ---
    ColeccionEnteros& operator=(const ColeccionEnteros& other) {
        std::cout << "DEBUG: Copy Assignment Operator called." << std::endl;

        // 1. Handle self-assignment (e.g., obj = obj;)
        if (this == &other) {
            return *this; // Return immediately
        }

        // 2. Free existing resources (important!)
        if (datos != nullptr) {
            delete[] datos;
            datos = nullptr; // Defensive programming
        }

        // 3. Allocate new memory and deep copy
        tamano = other.tamano;
        if (tamano > 0) {
            datos = new int[tamano];
            std::copy(other.datos, other.datos + tamano, datos);
        } else {
            datos = nullptr;
        }

        // 4. Return *this to allow chaining (e.g., obj3 = obj2 = obj1;)
        return *this;
    }
        #endif  //#if _COPY_ASSIGNMENT_OPE_

    // --- Métodos de la Clase ---

    // Obtener un elemento en una posición específica
    int obtener(int indice) const {
        if (indice >= 0 && indice < tamano) {
            return datos[indice];
        }
        std::cerr << "ERROR: Índice fuera de rango al obtener." << std::endl;
        return -1; // Valor de error
    }

    // Establecer un elemento en una posición específica
    void establecer(int indice, int valor) {
        if (indice >= 0 && indice < tamano) {
            datos[indice] = valor;
        } else {
            std::cerr << "ERROR: Índice fuera de rango al establecer." << std::endl;
        }
    }

    // Obtener el tamaño de la colección
    int getTamano() const {
        return tamano;
    }

    // Mostrar todos los elementos de la colección
    void mostrarElementos() const {
        std::cout << "Elementos de la colección (Tamaño: " << tamano << "): [";
        for (int i = 0; i < tamano; ++i) {
            std::cout << datos[i];
            if (i < tamano - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

// Función principal (main) para probar la clase
int main() {
    std::cout << "--- Program Start ---" << std::endl;

        #if _CTOR_AND_DTOR_
    // 1. Probar el Constructor por Defecto
    ColeccionEnteros c1; // Se crea un objeto vacío
    std::cout << "Tamaño de c1: " << c1.getTamano() << std::endl;
    c1.mostrarElementos();

    std::cout << "\n--- Creando una colección con 5 elementos (en el stack) ---" << std::endl;
    // 2. Probar el Constructor Parametrizado (en el stack)
    ColeccionEnteros c2(5); // Se crea un objeto con 5 elementos
    c2.establecer(0, 10);
    c2.establecer(1, 20);
    c2.establecer(2, 30);
    c2.establecer(3, 40);
    c2.establecer(4, 50);
    // Intentar establecer fuera de rango
    c2.establecer(5, 60);
    c2.mostrarElementos();
    std::cout << "Elemento en índice 2 de c2: " << c2.obtener(2) << std::endl;

    std::cout << "\n--- Creando una colección con 3 elementos (en el heap) ---" << std::endl;
    // 3. Probar el Constructor Parametrizado (en el heap)
    ColeccionEnteros* ptr_c3 = new ColeccionEnteros(3); // Se crea un objeto en el heap
    ptr_c3->establecer(0, 100);
    ptr_c3->establecer(1, 200);
    ptr_c3->establecer(2, 300);
    ptr_c3->mostrarElementos();

    std::cout << "\n--- Liberando la colección del heap ---" << std::endl;
    // ¡Muy importante! Llamar delete para que el destructor se invoque
    delete ptr_c3;
    ptr_c3 = nullptr; // Buenas prácticas
        #endif  //#if _CTOR_AND_DTOR_

        #if _COPY_CONSTRUCTOR_
    ColeccionEnteros c1(3);
    c1.establecer(0, 10);
    c1.establecer(1, 20);
    c1.establecer(2, 30);
    std::cout << "c1: "; c1.mostrarElementos();

    std::cout << "\n--- Creating c2 by copy-initializing from c1 ---" << std::endl;
    ColeccionEnteros c2 = c1; // Calls the Copy Constructor
    std::cout << "c2: "; c2.mostrarElementos();

    std::cout << "\n--- Modifying c1 (c2 should remain unchanged) ---" << std::endl;
    c1.establecer(0, 100);
    std::cout << "c1 after modification: "; c1.mostrarElementos();
    std::cout << "c2 (should be original): "; c2.mostrarElementos(); // c2 still has 10, 20, 30

    std::cout << "\n--- Program End ---" << std::endl;
        #endif  //#if _COPY_CONSTRUCTOR_

        #if _COPY_ASSIGNMENT_OPE_
    ColeccionEnteros c1(3);
    c1.establecer(0, 10);
    c1.establecer(1, 20);
    c1.establecer(2, 30);
    std::cout << "c1: "; c1.mostrarElementos();

    std::cout << "\n--- Creating c2 by copy-initializing from c1 ---" << std::endl;
    ColeccionEnteros c2 = c1; // Calls the Copy Constructor
    std::cout << "c2: "; c2.mostrarElementos();

    std::cout << "\n--- Creating c3, then assigning c1 to it ---" << std::endl;
    ColeccionEnteros c3(2); // c3 is already constructed, calls parametrized constructor
    c3.establecer(0, 99);
    c3.establecer(1, 88);
    std::cout << "c3 before assignment: "; c3.mostrarElementos();

    c3 = c1; // Calls the Copy Assignment Operator
    std::cout << "c3 after assignment from c1: "; c3.mostrarElementos();

    std::cout << "\n--- Modifying c1 again (c2 and c3 should remain unchanged) ---" << std::endl;
    c1.establecer(0, 1000);
    std::cout << "c1 after modification: "; c1.mostrarElementos();
    std::cout << "c2 (should be original): "; c2.mostrarElementos();
    std::cout << "c3 (should be copy of original c1): "; c3.mostrarElementos();
         #endif  //#if _COPY_ASSIGNMENT_OPE_

    std::cout << "\n--- Program End ---" << std::endl;
    // #_CTOR_AND_DTOR_: Aquí c1 y c2 salen del ámbito y sus destructores se llaman automáticamente.

    return 0;
}