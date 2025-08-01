// Example using std::vector (Rule of Zero in action)
#include <iostream>
#include <vector> // Includes std::vector

class ColeccionVector {
private:
    std::vector<int> datos; // std::vector handles its own memory!

public:
    // Default Constructor
    ColeccionVector() {
        std::cout << "DEBUG: Default Constructor for ColeccionVector called (empty)." << std::endl;
    }

    // Parametrized Constructor
    ColeccionVector(int n) : datos(n) { // std::vector constructor handles allocation
        std::cout << "DEBUG: Parametrized Constructor for ColeccionVector called. Size: "
                  << datos.size() << " elements." << std::endl;
    }

    // NO NEED to implement Copy Constructor, Copy Assignment Operator, or Destructor!
    // std::vector handles deep copying and memory management automatically.
    // The compiler-generated ones will correctly call std::vector's own copy/destroy methods.

    // Other methods
    int obtener(int indice) const {
        if (indice >= 0 && indice < datos.size()) {
            return datos[indice];
        }
        std::cerr << "ERROR: Index out of bounds on get." << std::endl;
        return -1;
    }

    void establecer(int indice, int valor) {
        if (indice >= 0 && indice < datos.size()) {
            datos[indice] = valor;
        } else {
            std::cerr << "ERROR: Index out of bounds on set." << std::endl;
        }
    }

    int getTamano() const {
        return datos.size();
    }

    void mostrarElementos() const {
        std::cout << "Collection elements (Size: " << datos.size() << "): [";
        for (int i = 0; i < datos.size(); ++i) {
            std::cout << datos[i];
            if (i < datos.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

int main() { // Using a different main name to avoid conflict
    std::cout << "\n--- Program Start (using std::vector) ---" << std::endl;

    ColeccionVector cv1(3);
    cv1.establecer(0, 10);
    cv1.establecer(1, 20);
    cv1.establecer(2, 30);
    std::cout << "cv1: "; cv1.mostrarElementos();

    std::cout << "\n--- Copy-initializing cv2 from cv1 ---" << std::endl;
    ColeccionVector cv2 = cv1; // Compiler-generated copy constructor works!
    std::cout << "cv2: "; cv2.mostrarElementos();

    std::cout << "\n--- Assigning cv1 to cv3 ---" << std::endl;
    ColeccionVector cv3;
    cv3 = cv1; // Compiler-generated copy assignment operator works!
    std::cout << "cv3: "; cv3.mostrarElementos();

    std::cout << "\n--- Program End (using std::vector) ---" << std::endl;
    return 0;
}