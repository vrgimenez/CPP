#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <algorithm>
#include <mutex>
#include <random>

// Mutex para proteger la salida estándar (std::cout)
std::mutex cout_mutex; 

/**
 * @brief Función ejecutada por cada hilo para procesar su segmento del vector.
 * @param data Referencia al vector compartido de enteros.
 * @param start_index Índice de inicio del segmento.
 * @param end_index Índice de fin del segmento (exclusivo).
 * @param thread_id Identificador del hilo para la impresión.
 */
void processSegment(std::vector<int>& data, int start_index, int end_index, int thread_id) {
    // 1. Iniciar un bloqueo para imprimir de forma segura
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Thread " << thread_id << ": Starting processing from index " 
              << start_index << " to " << end_index - 1 << std::endl;
    
    // 2. Realizar la tarea (ejemplo: sumar los valores del segmento)
    long long segment_sum = 0;
    for (int i = start_index; i < end_index; ++i) {
        segment_sum += data[i];
    }

    // 3. Imprimir el resultado de forma segura
    std::cout << "Thread " << thread_id << ": Sum of its 250 values is " 
              << segment_sum << std::endl;
}

int main() {
    // Definiciones del problema
    const int VECTOR_SIZE = 1000;
    const int NUM_THREADS = 4;
    const int SEGMENT_SIZE = VECTOR_SIZE / NUM_THREADS; // 1000 / 4 = 250

    // 1. Crear y llenar el vector de 1000 enteros aleatorios
    std::vector<int> shared_data(VECTOR_SIZE);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100); // Números aleatorios entre 1 y 100

    std::cout << "Main Thread: Generating " << VECTOR_SIZE << " random integers." << std::endl;
    // Rellenar el vector con números aleatorios
    std::generate(shared_data.begin(), shared_data.end(), [&]() { return distrib(gen); });

    // 2. Crear un array para almacenar los objetos std::thread
    std::thread threads[NUM_THREADS];

    // 3. Lanzar los 4 hilos, asignando cada segmento de 250 valores
    std::cout << "Main Thread: Launching " << NUM_THREADS << " threads." << std::endl;
    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * SEGMENT_SIZE;
        int end = start + SEGMENT_SIZE;
        
        // El constructor de std::thread lanza inmediatamente el hilo:
        // Se pasa el vector por referencia (std::ref) para evitar copias costosas.
        threads[i] = std::thread(processSegment, 
                                 std::ref(shared_data), // El vector compartido (por referencia)
                                 start,                // Índice de inicio
                                 end,                  // Índice de fin (exclusivo)
                                 i + 1                 // ID del hilo (1, 2, 3, 4)
                                );
    }

    // 4. Esperar a que todos los hilos terminen (join)
    std::cout << "Main Thread: Waiting for all threads to finish..." << std::endl;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i].join();
    }

    // 5. Verificar el resultado total (Opcional)
    long long total_sum = std::accumulate(shared_data.begin(), shared_data.end(), 0LL);
    std::cout << "Main Thread: All threads finished. Total expected sum: " << total_sum << std::endl;
    
    return 0;
}