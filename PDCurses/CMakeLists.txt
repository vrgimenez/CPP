# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.13)

# Nombre del proyecto
project(PNCursesCppExamples CXX)

# Establecer el estándar C++ (usa un estándar moderno)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directorio base donde se encuentra la librería PNCurses
set(PDCURSES_ROOT "c:/pdcurses")

# =========================================================
# 1. Incluir directorios y librerías de PNCurses
# =========================================================

# Incluir los directorios de cabecera (headers)
# PNCurses (donde están los archivos .h)
include_directories(${PDCURSES_ROOT})

# Directorio donde se encuentran los archivos .lib o .a
link_directories(${PDCURSES_ROOT}/wincon)

# =========================================================
# 2. Definir los ejecutables y sus dependencias
# =========================================================

# The example applications
set(EXECUTABLES
    3-SimplePrintwExample
    4-SimpleScanwExample
    5-SimpleAttributesExample
    6-ChgatUsageExample
    7-WindowBorderExample
    8-WindowBorderExample2
    9-ColorsExample
    10-SimpleKeyUsageExample
    11-SimpleKeyMouseUsageExample
    12-TemporarilyLeavingCursesModeExample
    13-ACSVariablesExample
)

## Build the example apps
foreach(EXECUTABLE ${EXECUTABLES})
    # Añade ejecutables
    add_executable(${EXECUTABLE} ${EXECUTABLE}.cpp)

    # Defino PNCURSES_STATIC
    target_compile_options(${EXECUTABLE} PUBLIC
        -O3
        -DNDEBUG
        -DNCURSES_STATIC
    )

    # Enlazar las librerías necesarias con el ejecutable
    target_link_libraries(${EXECUTABLE}
        # PNCurses
        pdcurses.a
        
        # Librerías de sistema adicionales que PNCurses puede necesitar en Windows
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
