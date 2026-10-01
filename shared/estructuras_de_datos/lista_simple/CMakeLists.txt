cmake_minimum_required(VERSION 3.16)

project(listaSimple LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/lista_simple.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)