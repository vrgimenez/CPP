#define _POLYMORPHISM_      1

#include <iostream>
#include <string>
    #if _POLYMORPHISM_
#include <memory> // For std::unique_ptr
    #endif  //#if _POLYMORPHISM_

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

        #if _POLYMORPHISM_
    // This is the virtual function that enables polymorphism
    virtual void hacerSonido() const {
        std::cout << nombre << " makes a generic animal sound." << std::endl;
    }
        #endif  //#if _POLYMORPHISM_

    // Virtual destructor is important for polymorphism, we will cover this later
    virtual ~Animal() {
        std::cout << "DEBUG: Animal base class destructor called for " << nombre << std::endl;
    }
};

    #if _POLYMORPHISM_
// --- Derived class overrides the virtual function ---
class Perro : public Animal {
private:
    std::string raza;

public:
    Perro(const std::string& nombre_perro, int edad_perro, const std::string& raza_perro)
        : Animal(nombre_perro, edad_perro), raza(raza_perro) {
        std::cout << "DEBUG: Perro derived class constructor called for " << nombre << std::endl;
    }

    // The 'override' keyword is a good practice to ensure we are overriding a virtual function
    void hacerSonido() const override {
        std::cout << nombre << " says: Woof! Woof!" << std::endl;
    }

        // Overriding the destructor from the base class
    ~Perro() override {
        std::cout << "DEBUG: Perro derived class destructor called for " << nombre << std::endl;
    }

};
    #endif  //#if _POLYMORPHISM_

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

        #if _POLYMORPHISM_
    void hacerSonido() const override {
        std::cout << nombre << " says: Meow! Meow!" << std::endl;
    }
        #else
    void maullar() const {
        std::cout << nombre << " the " << raza << " cat says: Meow!" << std::endl;
    }
        #endif  //#if _POLYMORPHISM_

    // Overriding the destructor from the base class
    ~Gato() override {
        std::cout << "DEBUG: Gato derived class destructor called for " << nombre << std::endl;
    }
};

    #if _POLYMORPHISM_
// A function that can take any derived class of Animal
void escucharAnimal(const Animal& animal) {
    animal.hacerSonido(); // This call is polymorphic!
}
    #endif  //#if _POLYMORPHISM_

int main() {
        #if _POLYMORPHISM_
    std::cout << "--- Polymorphic Behavior ---" << std::endl;

    Perro miPerro("Fido", 6, "Border Collie");
    Gato miGato("Garfield", 3, "Persa");

    // Calling a function with a reference to the base class
    escucharAnimal(miPerro); // Calls Perro's hacerSonido()
    escucharAnimal(miGato);  // Calls Gato's hacerSonido()

    std::cout << "\n--- Polymorphism with smart pointers ---" << std::endl;

    // A unique_ptr to the base class can hold a derived class object
    std::unique_ptr<Animal> animal1 = std::make_unique<Perro>("Snoopy", 4, "Beagle");
    std::unique_ptr<Animal> animal2 = std::make_unique<Gato>("Tom", 5, "Azul Ruso");

    // The call to hacerSonido() is polymorphic at runtime
    animal1->hacerSonido(); // Calls Perro's hacerSonido()
    animal2->hacerSonido(); // Calls Gato's hacerSonido()

    std::cout << "\n--- Program End. Objects will be destroyed ---" << std::endl;

        #else

    std::cout << "--- Creating a Gato object on the stack ---" << std::endl;
    Gato miGato("Whiskers", 3, "Siamese");

    std::cout << "\n--- Calling methods inherited from Animal ---" << std::endl;
    miGato.comer();

    std::cout << "\n--- Calling a method specific to Gato ---" << std::endl;
    miGato.maullar();

    std::cout << "\n--- Program End. Destructors will be called ---" << std::endl;
        #endif  //#if _POLYMORPHISM_

    return 0;
}
