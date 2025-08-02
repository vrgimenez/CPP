#define _CTOR_AND_DTOR_             0
#define _COPY_CONSTRUCTOR_          0
#define _COPY_ASSIGNMENT_OPE_       0
#define _MOVE_CTOR_AND_ASSGN_OPE_   1

#include <iostream> // Para std::cout y std::endl
    #if _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_ || _MOVE_CTOR_AND_ASSGN_OPE_
#include <algorithm> // For std::copy
    #endif  //#if _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_ || _MOVE_CTOR_AND_ASSGN_OPE_
    #if _MOVE_CTOR_AND_ASSGN_OPE_
#include <utility>   // For std::exchange, std::move
    #endif  //#if _MOVE_CTOR_AND_ASSGN_OPE_

class ColeccionEnteros {
private:
    int* datos;     // Puntero al array de enteros en el heap
    int tamano;     // Tamaño actual de la colección

public:
        #if _CTOR_AND_DTOR_ || _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_ || _MOVE_CTOR_AND_ASSGN_OPE_
    // --- Constructores ---

    // 1. Constructor por Defecto (Default Constructor)
    // Inicializa una colección vacía.
    ColeccionEnteros() : datos(nullptr), tamano(0) {
        std::cout << "DEBUG: Default Constructor called (empty)." << std::endl;
    }

    // 2. Constructor Parametrizado (Parametrized Constructor)
    // Crea una colección de un tamaño dado y asigna memoria.
    ColeccionEnteros(int n) : tamano(n) {
        if (tamano > 0) {
            datos = new int[tamano]; // Asignación de memoria en el heap
            std::cout << "DEBUG: Parametrized Constructor called. Memory allocated for "
                      << tamano << " elements." << std::endl;
            // Opcional: inicializar los elementos a 0
            for (int i = 0; i < tamano; ++i) {
                datos[i] = 0;
            }
        } else {
            datos = nullptr;
            tamano = 0;
            std::cout << "DEBUG: Parametrized Constructor called with invalid or zero size." << std::endl;
        }
    }

    // --- Destructor ---
    // Libera la memoria asignada cuando el objeto es destruido.
    ~ColeccionEnteros() {
        if (datos != nullptr) {
            delete[] datos; // Liberar el array de memoria
            datos = nullptr; // Buenas prácticas: evitar punteros colgantes
            std::cout << "DEBUG: Destructor called. Memory for "
                      << tamano << " elements freed." << std::endl;
        } else {
            std::cout << "DEBUG: Destructor called. No memory to free." << std::endl;
        }
    }
        #endif  //#if _CTOR_AND_DTOR_ || _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_ || _MOVE_CTOR_AND_ASSGN_OPE_

        #if _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_ || _MOVE_CTOR_AND_ASSGN_OPE_
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
        #endif  //#if _COPY_CONSTRUCTOR_ || _COPY_ASSIGNMENT_OPE_ || _MOVE_CTOR_AND_ASSGN_OPE_

        #if _MOVE_CTOR_AND_ASSGN_OPE_
    // --- Move Constructor ---
    // Takes an r-value reference to another object (likely a temporary).
    // "Steals" the resources from the source object.
    ColeccionEnteros(ColeccionEnteros&& other) noexcept
        : datos(std::exchange(other.datos, nullptr)), // Steal pointer, set other's pointer to nullptr
          tamano(std::exchange(other.tamano, 0)) {    // Steal size, set other's size to 0
        std::cout << "DEBUG: Move Constructor called. Resources moved." << std::endl;
    }
        #endif  //#if _MOVE_CTOR_AND_ASSGN_OPE_

        #if _COPY_ASSIGNMENT_OPE_ || _MOVE_CTOR_AND_ASSGN_OPE_
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
        #endif  //#if _COPY_ASSIGNMENT_OPE_ || _MOVE_CTOR_AND_ASSGN_OPE_

        #if _MOVE_CTOR_AND_ASSGN_OPE_
    // --- Move Assignment Operator ---
    // Takes an r-value reference to another object (likely a temporary).
    // Frees current resources, then "steals" resources from the source object.
    ColeccionEnteros& operator=(ColeccionEnteros&& other) noexcept {
        std::cout << "DEBUG: Move Assignment Operator called." << std::endl;

        // 1. Handle self-assignment (though less common with move)
        if (this == &other) {
            return *this;
        }

        // 2. Free existing resources of 'this' object
        if (datos != nullptr) {
            delete[] datos;
        }

        // 3. Steal resources from 'other'
        datos = std::exchange(other.datos, nullptr);
        tamano = std::exchange(other.tamano, 0);

        // 4. Return *this
        return *this;
    }
        #endif    //#if _MOVE_CTOR_AND_ASSGN_OPE_

    // --- Métodos de la Clase ---

    // Obtener un elemento en una posición específica
    int obtener(int indice) const {
        if (indice >= 0 && indice < tamano) {
            return datos[indice];
        }
        std::cerr << "ERROR: Index out of bounds on get." << std::endl;
        return -1; // Valor de error
    }

    // Establecer un elemento en una posición específica
    void establecer(int indice, int valor) {
        if (indice >= 0 && indice < tamano) {
            datos[indice] = valor;
        } else {
            std::cerr << "ERROR: Index out of bounds on set." << std::endl;
        }
    }

    // Obtener el tamaño de la colección
    int getTamano() const {
        return tamano;
    }

    // Mostrar todos los elementos de la colección
    void mostrarElementos() const {
        std::cout << "Collection elements (Size: " << tamano << "): [";
        for (int i = 0; i < tamano; ++i) {
            std::cout << datos[i];
            if (i < tamano - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

    #if _MOVE_CTOR_AND_ASSGN_OPE_
// Function that returns a ColeccionEnteros by value (will trigger move constructor)
ColeccionEnteros crearColeccionTemporal(int size) {
    ColeccionEnteros temp(size);
    for (int i = 0; i < size; ++i) {
        temp.establecer(i, (i + 1) * 10);
    }
    std::cout << "DEBUG: Inside crearColeccionTemporal. temp: "; temp.mostrarElementos();
    return temp; // This is an r-value, move constructor will be called (or NRVO)
}
    #endif    //#if _MOVE_CTOR_AND_ASSGN_OPE_

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

         #if _MOVE_CTOR_AND_ASSGN_OPE_
    ColeccionEnteros c1(3);
    c1.establecer(0, 10);
    c1.establecer(1, 20);
    c1.establecer(2, 30);
    std::cout << "c1: "; c1.mostrarElementos();

    std::cout << "\n--- Creating c2 by copy-initializing from c1 (L-value) ---" << std::endl;
    ColeccionEnteros c2 = c1; // Calls Copy Constructor (c1 is an L-value)
    std::cout << "c2: "; c2.mostrarElementos();

    std::cout << "\n--- Creating c3 by move-initializing from a temporary (R-value) ---" << std::endl;
    ColeccionEnteros c3 = crearColeccionTemporal(4); // Calls Move Constructor (return value is an R-value)
    std::cout << "c3: "; c3.mostrarElementos();

    std::cout << "\n--- Assigning a temporary to c4 (R-value assignment) ---" << std::endl;
    ColeccionEnteros c4(2);
    c4.establecer(0, 5);
    c4.establecer(1, 5);
    std::cout << "c4 before move assignment: "; c4.mostrarElementos();
    c4 = crearColeccionTemporal(5); // Calls Move Assignment Operator
    std::cout << "c4 after move assignment: "; c4.mostrarElementos();

    std::cout << "\n--- Explicitly moving c1's resources to c5 ---" << std::endl;
    // std::move converts an L-value into an R-value reference, forcing a move.
    // Use with caution: c1 will be in a valid but unspecified state after this!
    ColeccionEnteros c5 = std::move(c1); // Calls Move Constructor
    std::cout << "c5: "; c5.mostrarElementos();
    std::cout << "c1 after being moved (state is valid but unspecified, likely empty): "; c1.mostrarElementos();
         #endif //#if _MOVE_CTOR_AND_ASSGN_OPE_

    std::cout << "\n--- Program End ---" << std::endl;
    // #_CTOR_AND_DTOR: Aquí c1 y c2 salen del ámbito y sus destructores se llaman automáticamente.

    return 0;
}