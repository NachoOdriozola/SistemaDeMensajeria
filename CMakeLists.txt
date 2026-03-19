cmake_minimum_required(VERSION 3.16)

project(AplicacionDeMensajes LANGUAGES C)

add_compile_options(/utf-8)

add_subdirectory(shared/constantes)
add_subdirectory(shared/protocolos)
add_subdirectory(shared/estructurasDeDatos/nodo)
add_subdirectory(shared/estructurasDeDatos/listaSimple)
add_subdirectory(shared/estructurasDeDatos/listaCircular)
add_subdirectory(shared/estructurasDeDatos/tablaHash)

add_subdirectory(external/sqlite)
add_subdirectory(external/csfml)

add_subdirectory(server)
add_subdirectory(client)