#include <iostream>
#include <string>
#include <vector>
#include <memory>

// --- Abstract Base Class: Shape ---
// It cannot be instantiated directly because it contains a pure virtual function.
class Shape {
protected:
    std::string color;
    
public:
    Shape(const std::string& color) : color(color) {}

    // Pure virtual function. It MUST be overridden by derived classes.
    virtual double getArea() const = 0;

    // A regular virtual function that can be overridden but doesn't have to be.
    virtual void printInfo() const {
        std::cout << "This is a " << color << " shape." << std::endl;
    }

    // A pure virtual destructor. This is also possible, but requires an implementation.
    virtual ~Shape() = 0;
};

// --- Implementation of the pure virtual destructor ---
// It must have an implementation outside the class definition.
// This is necessary to ensure the destructor chain is called correctly.
Shape::~Shape() {
    std::cout << "DEBUG: Shape base class destructor called." << std::endl;
}

// --- Derived Class: Circle ---
class Circle : public Shape {
private:
    double radius;

public:
    Circle(const std::string& color, double radius) 
        : Shape(color), radius(radius) {}

    // We must override getArea() because it's a pure virtual function in the base class.
    double getArea() const override {
        return 3.14159 * radius * radius;
    }

    void printInfo() const override {
        std::cout << "This is a " << color << " circle with a radius of " << radius << "." << std::endl;
    }
};

// --- Derived Class: Rectangle ---
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(const std::string& color, double width, double height) 
        : Shape(color), width(width), height(height) {}

    // We must override getArea() to implement its specific behavior.
    double getArea() const override {
        return width * height;
    }

    // We choose not to override printInfo(), so it will use the base class's version.
};

int main() {
    std::cout << "--- Abstract Class Example ---" << std::endl;

    // --- Create a vector of unique_ptr to the abstract base class ---
    std::vector<std::unique_ptr<Shape>> shapes;
    
    // We can't do this: Shape genericShape("red"); // This would cause a compile error!

    // We can only store derived objects in our vector of base pointers.
    shapes.push_back(std::make_unique<Circle>("blue", 5.0));
    shapes.push_back(std::make_unique<Rectangle>("green", 4.0, 6.0));

    std::cout << "\n--- Displaying shape information and area ---" << std::endl;
    for (const auto& shape : shapes) {
        // The getArea() call is polymorphic, calling the correct derived method.
        std::cout << "Area: " << shape->getArea() << std::endl;
        shape->printInfo();
        std::cout << "---------------------------------" << std::endl;
    }

    std::cout << "\n--- Program End. Objects will be automatically freed ---" << std::endl;
    return 0;
}