#include <iostream>
#include <string>
#include <vector>
#include <memory> // For unique_ptr

// --- Abstract Base Class ---
class Notificacion {
public:
    virtual void enviar(const std::string& mensaje) const = 0;
    virtual ~Notificacion() = default;
};

// --- Derived Class 1: Email Notification ---
class EmailNotificacion : public Notificacion {
public:
    void enviar(const std::string& mensaje) const override {
        std::cout << "DEBUG: Enviando email con el mensaje: '" << mensaje << "'" << std::endl;
    }
};

// --- Derived Class 2: SMS Notification ---
class SMSNotificacion : public Notificacion {
public:
    void enviar(const std::string& mensaje) const override {
        std::cout << "DEBUG: Enviando SMS con el mensaje: '" << mensaje << "'" << std::endl;
    }
};

int main() {
    std::cout << "--- Sistema de Notificaciones ---" << std::endl;

    std::vector<std::unique_ptr<Notificacion>> canales_de_notificacion;

    // Create unique_ptr to derived types and add to vector
    canales_de_notificacion.push_back(std::make_unique<EmailNotificacion>());
    canales_de_notificacion.push_back(std::make_unique<SMSNotificacion>());

    std::cout << "\n--- Enviando mensajes a todos los canales ---" << std::endl;
    std::string mensaje_importante = "¡Tu pedido ha sido enviado!";

    for (const auto& canal : canales_de_notificacion) {
        canal->enviar(mensaje_importante); // Polymorphic call
    }

    std::cout << "\n--- Fin del programa. Objetos liberados. ---" << std::endl;
    return 0;
}