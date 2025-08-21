#include <iostream>
#include <string>
#include <vector>
#include <memory> // For unique_ptr

// --- Base Class ---
class Libro {
protected:
    std::string titulo;
    std::string autor;
    double precio;

public:
    Libro(const std::string& titulo, const std::string& autor, double precio)
        : titulo(titulo), autor(autor), precio(precio) {
        std::cout << "DEBUG: Libro base class constructor called: " << titulo << std::endl;
    }

    virtual std::string obtenerTipo() const {
        return "Libro generico";
    }

    virtual void mostrarDetalles() const {
        std::cout << "Title: " << titulo << ", Author: " << autor << ", Price: $" << precio << std::endl;
    }

    virtual ~Libro() {
        std::cout << "DEBUG: Libro base class destructor called: " << titulo << std::endl;
    }
};

// --- Derived Class 1: Textbook ---
class LibroDeTexto : public Libro {
private:
    std::string materia;

public:
    // TODO: Implement the constructor for LibroDeTexto
    LibroDeTexto(const std::string& titulo, const std::string& autor, double precio, const std::string& materia) 
        : Libro(titulo, autor, precio), materia(materia) {
        // TODO: Call the base class constructor and initialize 'materia'
        std::cout << "DEBUG: LibroDeTexto derived class constructor called for " << titulo << std::endl;
    }

    // TODO: Override the virtual function to return a specific type
    std::string obtenerTipo() const override {
        // TODO: Return "Libro de Texto"
        return "Libro de Texto";
    }

    void mostrarDetalles() const override {
        Libro::mostrarDetalles(); // Call the base class method to show common details
        std::cout << "   - Type: Libro de Texto, Subject: " << materia << std::endl;
    }
};

// --- Derived Class 2: Novel ---
class Novela : public Libro {
private:
    std::string genero;

public:
    // TODO: Implement the constructor for Novela
    Novela(const std::string& titulo, const std::string& autor, double precio, const std::string& genero)
        : Libro(titulo, autor, precio), genero(genero) {
        // TODO: Call the base class constructor and initialize 'genero'
        std::cout << "DEBUG: Novela derived class constructor called for " << titulo << std::endl;
    }

    // TODO: Override the virtual function to return a specific type
    std::string obtenerTipo() const override {
        // TODO: Return "Novela"
        return "Novela";
    }

    void mostrarDetalles() const override {
        Libro::mostrarDetalles();
        std::cout << "   - Type: Novela, Genre: " << genero << std::endl;
    }
};

// --- Main function to test the classes ---
int main() {
    std::cout << "--- Creating an inventory of books ---" << std::endl;
    // We use unique_ptr to manage the dynamic memory
    std::vector<std::unique_ptr<Libro>> inventario;

    // We can store different derived types in a vector of base class pointers
    // TODO: Create a LibroDeTexto and a Novela and add them to the inventory
    inventario.push_back(std::make_unique<LibroDeTexto>("Matemática 1", "Darío Tuffilaro", 33000, "Matemática"));
    inventario.push_back(std::make_unique<Novela>("El Camino de Sherlock", "Andrea Ferrari", 20900, "Misterio"));

    std::cout << "\n--- Displaying inventory details and types using polymorphism ---" << std::endl;

    for (const auto& libro : inventario) {
        libro->mostrarDetalles();
        std::cout << "   - This is a " << libro->obtenerTipo() << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }

    std::cout << "\n--- Program End. Objects will be automatically freed ---" << std::endl;
    // The unique_ptr objects go out of scope, their destructors are called,
    // which in turn call the destructors of the objects they own, and memory is freed.
    return 0;
}