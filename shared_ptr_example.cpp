#include <iostream>
#include <memory>  // For std::shared_ptr

class Recurso {
public:
    Recurso() { std::cout << "DEBUG: Recurso creado." << std::endl; }
    ~Recurso() { std::cout << "DEBUG: Recurso destruido." << std::endl; }
};

void usarRecurso(std::shared_ptr<Recurso> recurso) {
    std::cout << "DEBUG: Usando el recurso. Contador: " << recurso.use_count() << std::endl;
}

int main() {
    std::cout << "--- Shared Ptr Example ---" << std::endl;

    std::shared_ptr<Recurso> ptr1 = std::make_shared<Recurso>();
    std::cout << "DEBUG: ptr1 creado. Contador: " << ptr1.use_count() << std::endl;

    {
        std::shared_ptr<Recurso> ptr2 = ptr1; // Copying ptr1. Counter is now 2.
        std::cout << "DEBUG: ptr2 creado. Contador: " << ptr1.use_count() << std::endl;
        usarRecurso(ptr1); // Passing by value. A temporary shared_ptr is created. Counter is now 3.
        std::cout << "DEBUG: Despues de usarRecurso. Contador: " << ptr1.use_count() << std::endl;
    } // ptr2 and the temporary shared_ptr go out of scope. Counter goes back to 1.

    std::cout << "DEBUG: Saliendo del bloque. Contador: " << ptr1.use_count() << std::endl;

    // main ends, ptr1 goes out of scope, counter becomes 0, and the resource is destroyed.
    return 0;
}