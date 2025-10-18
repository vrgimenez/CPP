#include <iostream>
#include <string>
#include <vector>
#include <memory> 

// --- Abstract Base Class ---
class Notificacion {
public:
    // This is the polymorphic method that accepts the message.
    virtual void enviar(const std::string& mensaje) const = 0;
    virtual ~Notificacion() = default;
};

// --- Derived Class 1: Email Notification ---
class EmailNotificacion : public Notificacion {
private:
    std::string subject;

public:
    // The constructor now takes a specific argument (the email subject).
    EmailNotificacion(const std::string& subject) : subject(subject) {
        std::cout << "DEBUG: EmailNotificacion created." << std::endl;
    }

    // The polymorphic method uses both the received message and the stored data.
    void enviar(const std::string& mensaje) const override {
        std::cout << "DEBUG: Sending Email with Subject: '" << subject << "'" << std::endl;
        std::cout << "Message: '" << mensaje << "'" << std::endl;
    }
};

// --- Derived Class 2: SMS Notification ---
class SMSNotificacion : public Notificacion {
private:
    std::string phoneNumber;

public:
    // The constructor takes a different specific argument (the phone number).
    SMSNotificacion(const std::string& phoneNumber) : phoneNumber(phoneNumber) {
        std::cout << "DEBUG: SMSNotificacion created." << std::endl;
    }

    // This method uses both the received message and the stored data.
    void enviar(const std::string& mensaje) const override {
        std::cout << "DEBUG: Sending SMS to " << phoneNumber << std::endl;
        std::cout << "Message: '" << mensaje << "'" << std::endl;
    }
};

int main() {
    std::cout << "--- Sistema de Notificaciones ---" << std::endl;

    std::vector<std::unique_ptr<Notificacion>> canales_de_notificacion;

    // We now pass constructor arguments when creating the objects.
    canales_de_notificacion.push_back(std::make_unique<EmailNotificacion>("Important Update"));
    canales_de_notificacion.push_back(std::make_unique<SMSNotificacion>("555-1234567"));

    std::cout << "\n--- Enviando mensajes a todos los canales ---" << std::endl;
    std::string mensaje_importante = "¡Tu pedido ha sido enviado!";

    for (const auto& canal : canales_de_notificacion) {
        canal->enviar(mensaje_importante); 
    }

    std::cout << "\n--- Fin del programa. Objetos liberados. ---" << std::endl;
    return 0;
}