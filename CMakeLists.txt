# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Main01App LANGUAGES CXX) # Indica que es un proyecto C++

# Especifica el estándar C++ a usar (por ejemplo, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Añadir el ejecutables
add_executable(main01 main01.cpp)
add_executable(main02 main02.cpp)

# --- Configuración para Debug y Release ---

# 1. Modo Debug (por defecto si no se especifica otro)
# En modo Debug, CMake y el compilador:
# - Habilitan símbolos de depuración (-g en GCC/Clang)
# - Deshabilitan optimizaciones (o usan -O0)
# - No definen NDEBUG
target_compile_options(main01 PUBLIC
    $<$<CONFIG:Debug>:-g>               # Asegura -g para Debug
    $<$<CONFIG:Debug>:-O0>              # Sin optimizaciones para Debug
)
target_compile_options(main02 PUBLIC
    $<$<CONFIG:Debug>:-g>               # Asegura -g para Debug
    $<$<CONFIG:Debug>:-O0>              # Sin optimizaciones para Debug
)

# 2. Modo Release
# En modo Release, CMake y el compilador:
# - Eliminan símbolos de depuración (-s o -g0 en GCC/Clang)
# - Habilitan optimizaciones (-O2, -O3, -Os)
# - Definen NDEBUG (que desactiva 'assert' y otras comprobaciones)
target_compile_options(main01 PUBLIC
    $<$<CONFIG:Release>:-O3>            # Optimización para velocidad en Release
    $<$<CONFIG:Release>:-DNDEBUG>       # Define NDEBUG para Release
)
target_compile_options(main02 PUBLIC
    $<$<CONFIG:Release>:-O3>            # Optimización para velocidad en Release
    $<$<CONFIG:Release>:-DNDEBUG>       # Define NDEBUG para Release
)

# **NO FUNCIONA** Para eliminar los símbolos de depuración en el binario final (opcional, pero buena práctica para Release)
# Añadir sufijos a los binarios (opcional, pero útil)
set_target_properties(main01 PROPERTIES
    DEBUG_POSTFIX "_debug"             # Añade un sufijo a los binarios Debug (ej: MiApp_debug)
    RELEASE_POSTFIX "_release"         # Añade un sufijo a los binarios Release (ej: MiApp_release)
   #CMAKE_EXE_LINKER_FLAGS_RELEASE "-s" # **NO FUNCIONA** Quita los símbolos de depuración en el enlace final para Release
)
set_target_properties(main02 PROPERTIES
    DEBUG_POSTFIX "_debug"             # Añade un sufijo a los binarios Debug (ej: MiApp_debug)
    RELEASE_POSTFIX "_release"         # Añade un sufijo a los binarios Release (ej: MiApp_release)
   #CMAKE_EXE_LINKER_FLAGS_RELEASE "-s" # **NO FUNCIONA** Quita los símbolos de depuración en el enlace final para Release
)

# **ÉSTO SI FUNCIONA!!!** Usa target_link_options para pasar -s al enlazador solo en modo Release.
target_link_options(main01 PUBLIC
    $<$<CONFIG:Release>:-s>
)
target_link_options(main02 PUBLIC
    $<$<CONFIG:Release>:-s>
)

# Puedes definir opciones predeterminadas para los flags del compilador
# (Aunque las target_compile_options son más específicas)
# set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")