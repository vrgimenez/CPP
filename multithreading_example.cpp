#include <iostream>
#include <thread>
#include <chrono>

// Función que será ejecutada por el primer hilo
void tarea_hilo_1() {
    std::cout << "Hilo 1: Iniciando tarea..." << std::endl;
    // Simular un trabajo que toma tiempo
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Hilo 1: Tarea completada." << std::endl;
}

// Función que será ejecutada por el segundo hilo
void tarea_hilo_2(int id) {
    std::cout << "Hilo 2 (ID " << id << "): Iniciando cálculo..." << std::endl;
    long long suma = 0;
    for (int i = 0; i < 1000000; ++i) {
        suma += i;
    }
    std::cout << "Hilo 2 (ID " << id << "): Suma total = " << suma << ". Cálculo terminado." << std::endl;
}

int main() {
    std::cout << "Hilo Principal: Creando hilos..." << std::endl;

    // 1. Creación del primer hilo.
    // Inicia inmediatamente la ejecución de 'tarea_hilo_1'
    std::thread hilo1(tarea_hilo_1);

    // 2. Creación del segundo hilo, pasándole un argumento (el ID).
    // Inicia inmediatamente la ejecución de 'tarea_hilo_2(42)'
    int thread_id = 42;
    std::thread hilo2(tarea_hilo_2, thread_id);

    std::cout << "Hilo Principal: Hilos creados y ejecutándose." << std::endl;

    // 3. El hilo principal espera a que el 'hilo1' termine.
    // Es crucial llamar a 'join()' o 'detach()' para gestionar el hilo.
    std::cout << "Hilo Principal: Esperando a que el Hilo 1 termine (join)..." << std::endl;
    hilo1.join();

    // 4. El hilo principal espera a que el 'hilo2' termine.
    std::cout << "Hilo Principal: Esperando a que el Hilo 2 termine (join)..." << std::endl;
    hilo2.join();

    std::cout << "Hilo Principal: Ambos hilos han terminado. Finalizando programa." << std::endl;

    return 0;
}