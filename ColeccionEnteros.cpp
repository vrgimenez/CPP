#include <iostream> // Para std::cout y std::endl

class ColeccionEnteros {
private:
    int* datos;     // Puntero al array de enteros en el heap
    int tamano;     // Tamaño actual de la colección

public:
    // --- Constructores ---

    // 1. Constructor por Defecto
    // Inicializa una colección vacía.
    ColeccionEnteros() : datos(nullptr), tamano(0) {
        std::cout << "DEBUG: Constructor por defecto de ColeccionEnteros llamado (vacía)." << std::endl;
    }

    // 2. Constructor Parametrizado
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
    std::cout << "--- Inicio del programa ---" << std::endl;

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

    std::cout << "\n--- Fin del programa ---" << std::endl;
    // Aquí c1 y c2 salen del ámbito y sus destructores se llaman automáticamente.
    return 0;
}