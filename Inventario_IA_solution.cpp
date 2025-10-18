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
    LibroDeTexto(const std::string& titulo, const std::string& autor, double precio, const std::string& materia) 
        : Libro(titulo, autor, precio), materia(materia) {
        std::cout << "DEBUG: LibroDeTexto derived class constructor called." << std::endl;
    }

    std::string obtenerTipo() const override {
        return "Libro de Texto";
    }

    void mostrarDetalles() const override {
        Libro::mostrarDetalles();
        std::cout << "   - Type: Libro de Texto, Subject: " << materia << std::endl;
    }
};

// --- Derived Class 2: Novel ---
class Novela : public Libro {
private:
    std::string genero;

public:
    Novela(const std::string& titulo, const std::string& autor, double precio, const std::string& genero)
        : Libro(titulo, autor, precio), genero(genero) {
        std::cout << "DEBUG: Novela derived class constructor called." << std::endl;
    }

    std::string obtenerTipo() const override {
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
    std::vector<std::unique_ptr<Libro>> inventario;

    inventario.push_back(std::make_unique<LibroDeTexto>("C++ for Dummies", "Stephen Davis", 29.99, "Computer Science"));
    inventario.push_back(std::make_unique<Novela>("The Martian", "Andy Weir", 14.50, "Science Fiction"));

    std::cout << "\n--- Displaying inventory details and types using polymorphism ---" << std::endl;

    for (const auto& libro : inventario) {
        libro->mostrarDetalles();
        std::cout << "   - This is a " << libro->obtenerTipo() << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }

    std::cout << "\n--- Program End. Objects will be automatically freed ---" << std::endl;
    return 0;
}