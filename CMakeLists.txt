cmake_minimum_required(VERSION 3.20)

project(SistemaDeMensajeria LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(shared/constantes)
add_subdirectory(shared/protocolos)
add_subdirectory(shared/sockets)
add_subdirectory(shared/logs)
add_subdirectory(shared/estructuras_de_datos/lista_doble)
add_subdirectory(shared/estructuras_de_datos/cola)
add_subdirectory(shared/estructuras_de_datos/tabla_hash)

add_subdirectory(server)

if (WIN32)
    add_subdirectory(client)
endif()