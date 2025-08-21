#include <iostream>
#include <string>

// --- Base class ---
class Animal {
protected:
    std::string nombre;
    int edad;

public:
    // Constructor for the base class
    Animal(const std::string& nombre_animal, int edad_animal)
        : nombre(nombre_animal), edad(edad_animal) {
        std::cout << "DEBUG: Animal base class constructor called for " << nombre << std::endl;
    }

    void comer() const {
        std::cout << nombre << " is eating." << std::endl;
    }
    
    // Virtual destructor is important for polymorphism, we will cover this later
    virtual ~Animal() {
        std::cout << "DEBUG: Animal base class destructor called for " << nombre << std::endl;
    }
};

// --- Derived class ---
class Gato : public Animal {
private:
    std::string raza;

public:
    // Constructor for the derived class
    Gato(const std::string& nombre_gato, int edad_gato, const std::string& raza_gato)
        : Animal(nombre_gato, edad_gato), raza(raza_gato) {
        std::cout << "DEBUG: Gato derived class constructor called for " << nombre << std::endl;
    }

    void maullar() const {
        std::cout << nombre << " the " << raza << " cat says: Meow!" << std::endl;
    }

    // Overriding the destructor from the base class
    ~Gato() override {
        std::cout << "DEBUG: Gato derived class destructor called for " << nombre << std::endl;
    }
};

int main() {
    std::cout << "--- Creating a Gato object on the stack ---" << std::endl;
    Gato miGato("Whiskers", 3, "Siamese");

    std::cout << "\n--- Calling methods inherited from Animal ---" << std::endl;
    miGato.comer();

    std::cout << "\n--- Calling a method specific to Gato ---" << std::endl;
    miGato.maullar();

    std::cout << "\n--- Program End. Destructors will be called ---" << std::endl;
    return 0;
}