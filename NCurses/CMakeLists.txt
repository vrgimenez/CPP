# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.13)

# Nombre del proyecto
project(NCursesCppExamples CXX)

# Establecer el estándar C++ (usa un estándar moderno)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directorio base donde se encuentra la librería NCurses
set(NCURSES_ROOT "c:/ncurses")

# =========================================================
# 1. Incluir directorios y librerías de NCurses
# =========================================================

# Incluir los directorios de cabecera (headers)
# NCurses (donde están los archivos .h)
include_directories(${NCURSES_ROOT}/include/ncursesw)

# Directorio donde se encuentran los archivos .lib o .a
link_directories(${NCURSES_ROOT}/lib)

# =========================================================
# 2. Definir los ejecutables y sus dependencias
# =========================================================

# The example applications
set(EXECUTABLES
    NCursesMain
    NCursesExamples
)

## Build the example apps
foreach(EXECUTABLE ${EXECUTABLES})
    # Añade ejecutables
    add_executable(${EXECUTABLE} ${EXECUTABLE}.cpp)

    # Defino NCURSES_STATIC
    target_compile_options(${EXECUTABLE} PUBLIC
        -O3
        -DNDEBUG
        -DNCURSES_STATIC
    )

    # Enlazar las librerías necesarias con el ejecutable
    target_link_libraries(${EXECUTABLE}
        # NCurses
        ncursesw.a
        
        # Librerías de sistema adicionales que NCurses puede necesitar en Windows
        # rpcrt4
        # ws2_32
        # advapi32
        # crypt32
        
        # Librería de hilos estándar (puede ser necesaria en algunos sistemas)
        # pthread
    )

    # Usa target_link_options para pasar -s (strip symbols) al linker solo en modo Release.
    target_link_options(${EXECUTABLE} PUBLIC -s)

endforeach()
