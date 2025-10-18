#include <iostream>
#include <string>
#include <vector>
#include <memory> 

// 1. La estructura de datos genérica (Payload)
struct DatosMensaje {
    std::string cuerpo_texto;
    std::string asunto_email; // Solo relevante para Email
    std::string numero_telefono; // Solo relevante para SMS (si no está en el constructor)
    // Podríamos añadir int prioridad, bool tiene_adjunto, etc.
};

// --- Abstract Base Class (Interface remains clean) ---
class Notificacion {
public:
    // 2. El contrato polimórfico usa el objeto de datos.
    virtual void enviar(const DatosMensaje& datos) const = 0;
    virtual ~Notificacion() = default;
};

// --- Derived Class 1: Email Notification ---
class EmailNotificacion : public Notificacion {
public:
    // El constructor sigue siendo específico si lo necesitamos (e.g., para credenciales).
    EmailNotificacion() { /* ... */ }

    // El método enviar() accede solo a los datos relevantes.
    void enviar(const DatosMensaje& datos) const override {
        // Usa el asunto, ignora el número de teléfono.
        std::cout << "DEBUG: Sending Email with Subject: '" << datos.asunto_email << "'" << std::endl;
        std::cout << "To: (Destinatario del Objeto) - Message: '" << datos.cuerpo_texto << "'" << std::endl;
        // Podrías añadir lógica aquí para comprobar si datos.asunto_email está vacío, etc.
    }
};

// --- Derived Class 2: SMS Notification ---
class SMSNotificacion : public Notificacion {
private:
    std::string phoneNumber; // Mantenemos el número en el objeto, pero también podríamos usar el payload.
public:
    SMSNotificacion(const std::string& phoneNumber) : phoneNumber(phoneNumber) {}

    // El método enviar() accede solo a los datos relevantes.
    void enviar(const DatosMensaje& datos) const override {
        // Usa el número almacenado y el cuerpo del mensaje, ignora el asunto.
        std::cout << "DEBUG: Sending SMS to " << phoneNumber << std::endl;
        std::cout << "Message: '" << datos.cuerpo_texto << "'" << std::endl;
    }
};

int main() {
    std::cout << "--- Sistema de Notificaciones con Payload ---" << std::endl;

    std::vector<std::unique_ptr<Notificacion>> canales_de_notificacion;

    // Los constructores son específicos (siguen configurando la conexión).
    canales_de_notificacion.push_back(std::make_unique<EmailNotificacion>());
    canales_de_notificacion.push_back(std::make_unique<SMSNotificacion>("555-9876543"));

    std::cout << "\n--- Preparando el Payload ---" << std::endl;

    // 3. El cliente (main) prepara el objeto de datos completo para todos los canales.
    DatosMensaje payload {
        "¡Tu factura mensual ya está disponible!", // cuerpo_texto
        "Nueva Factura - Diciembre",              // asunto_email
        "",                                       // numero_telefono (no lo usaremos aquí, pero está disponible)
    };

    for (const auto& canal : canales_de_notificacion) {
        canal->enviar(payload); // La llamada es simple y polimórfica.
    }

    std::cout << "\n--- Fin del programa. ---" << std::endl;
    return 0;
}