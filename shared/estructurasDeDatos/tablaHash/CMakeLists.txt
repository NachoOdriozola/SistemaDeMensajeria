cmake_minimum_required(VERSION 3.16)

project(tablaHash LANGUAGES C)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/tablaHash.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC listaDoble)