#include <ncurses.h>

int main() {
    // Inicializa la pantalla
    initscr();

    // Mueve el cursor a la fila 5, columna 10 y escribe
    move(5, 10);
    printw("¡Hola en una posición específica!");

    // Mueve el cursor a la fila 8, columna 5 y escribe
    move(8, 5);
    printw("Otro mensaje aquí.");

    // Refresca la pantalla para mostrar los cambios
    refresh();

    // Espera una pulsación de tecla para salir
    getch();

    // Finaliza NCurses
    endwin();

    return 0;
}
