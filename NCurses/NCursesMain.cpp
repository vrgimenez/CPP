#define _LINUXANSI_ 1

#include <iostream>
    #if(_LINUXANSI_)
#include <locale>
    #else
#include <windows.h>
    #endif
#include <curses.h>

// gotoxy() Windows and Linux implementations
void gotoxy(int x, int y) {
        #if(_LINUXANSI_)
    printf("\033[%d;%df", y, x);
        #else
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #endif
}

    #if(!_LINUXANSI_)
void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Obtiene el tamaño del búfer de la pantalla de la consola
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Llena la pantalla con espacios en blanco
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten)) {
        return;
    }

    // Vuelve a colocar el cursor al inicio
    SetConsoleCursorPosition(hConsole, coordScreen);
}
    #endif

int main() {

        #if(_LINUXANSI_)
    // Establece la configuración regional del programa para que coincida con la del sistema.
    std::setlocale(LC_ALL, "es_ES.UTF-8");
        #else
    // Cambia la codificación de entrada y salida de la consola a UTF8
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
        #endif

    std::cout << "Esto es una prueba con tildes y la letra ñ: áéíóúñ" << std::endl;

    std::cout << "\nPresione 'Enter' para Ejemplo con ";
        #if(_LINUXANSI_)
    std::cout << "Linux(ANSI escape codes).\n" << std::endl;
        #else
    std::cout << "Windows Console API(windows.h).\n" << std::endl;
        #endif
    std::cin.get();

    // Limpia la pantalla y mueve el cursor a (0,0)
        #if(_LINUXANSI_)
    printf("\033[2J");
        #else
    clearScreen();
        #endif

    // Ubica el cursor en la columna 10, fila 5
    gotoxy(10, 5);
    std::cout << "¡Hola en una posición específica!";

    // Mueve el cursor a otra posición
    gotoxy(5, 8);
    std::cout << "Otro mensaje aquí.";

    /* ------------------------------------------------------------------ */

    gotoxy(0, 15);
    std::cout << "\nPresiona 'Enter' para Ejemplo de NCurses." << std::endl;
    std::cout << "Desde la Consola puede hacer falta ejecutar";
        #if(_LINUXANSI_)
    std::cout << " 'export TERM=xterm' (Linux)." << std::endl;
        #else
    std::cout << " 'set TERM=xterm' (Windows)." << std::endl;
        #endif
    std::cin.get();

    // Reestablezco la configuración regional (sino provoca 'Segmentation fault')
        #if(_LINUXANSI_)
    std::setlocale(LC_ALL, "");
        #endif

    // Limpia la pantalla y mueve el cursor a (0,0)
        #if(_LINUXANSI_)
    printf("\033[2J");
        #else
    clearScreen();
        #endif

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
