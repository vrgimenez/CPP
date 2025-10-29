#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
    #ifdef _WIN32
#include <Windows.h>
    #endif

std::atomic<bool> parar_hilo = false; // La bandera atómica

void tarea_detachable() {
    int contador = 0;
    while (!parar_hilo.load() && contador < 1000) {
        // El hilo chequea la bandera antes de cada ciclo de trabajo
        std::cout << "Hilo Detached: Trabajando..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        contador++;
    }
    std::cout << "Hilo Detached: **FIN** (parada cooperativa o trabajo terminado)." << std::endl;
}

int main() {
        #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
        #endif

    std::thread hilo_desconectado(tarea_detachable);
    hilo_desconectado.detach(); // El hilo principal pierde el control

    std::cout << "Hilo Principal: El hilo se está ejecutando en segundo plano..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera 1 segundo

    // 1. El hilo principal establece la bandera para señalizar la parada
    parar_hilo.store(true); 
    std::cout << "Hilo Principal: Señal enviada para detener el hilo." << std::endl;

    // 2. Espera un poco para que el hilo termine de notar la señal
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Nota: ¡El hilo ya terminó su ejecución y sus recursos se liberaron automáticamente!
    return 0;
}