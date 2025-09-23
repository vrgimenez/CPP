#include <iostream>
#include <string>
#include <vector>
#include <memory> // For unique_ptr

// --- Abstract Base Class ---
class Notificacion {
public:
    // Pure virtual function. It forces derived classes to provide an implementation.
    virtual void enviar(const std::string& mensaje) const = 0;

    // A virtual destructor is required for base classes with virtual functions.
    virtual ~Notificacion() = default;
};

// --- Derived Class 1: Email Notification ---
class EmailNotificacion : public Notificacion {
public:
    // TODO: Implement the enviar() method for email notification.
    void enviar(const std::string& mensaje) const override {
        // TODO: Print a message showing the email is being sent.
    }
};

// --- Derived Class 2: SMS Notification ---
class SMSNotificacion : public Notificacion {
public:
    // TODO: Implement the enviar() method for SMS notification.
    void enviar(const std::string& mensaje) const override {
        // TODO: Print a message showing the SMS is being sent.
    }
};

int main() {
    std::cout << "--- Sistema de Notificaciones ---" << std::endl;

    // We can't do this because Notificacion is an abstract class:
    // Notificacion notif;

    // Use a vector to store different types of notifications polymorphically.
    std::vector<std::unique_ptr<Notificacion>> canales_de_notificacion;

    // TODO: Create a unique_ptr to an EmailNotificacion and an SMSNotificacion
    //       and add them to the vector.
    
    // Example:
    // canales_de_notificacion.push_back(std::make_unique<...>(...));
    // canales_de_notificacion.push_back(std::make_unique<...>(...));

    std::cout << "\n--- Enviando mensajes a todos los canales ---" << std::endl;
    std::string mensaje_importante = "¡Tu pedido ha sido enviado!";

    for (const auto& canal : canales_de_notificacion) {
        canal->enviar(mensaje_importante); // Polymorphic call
    }

    std::cout << "\n--- Fin del programa. Objetos liberados. ---" << std::endl;
    return 0;
}