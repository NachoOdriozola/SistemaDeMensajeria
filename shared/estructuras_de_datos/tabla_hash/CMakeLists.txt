cmake_minimum_required(VERSION 3.16)

project(tablaHash LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/tabla_hash.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC listaDoble constantes logs)