cmake_minimum_required(VERSION 3.16)

project(listaDoble LANGUAGES C)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/listaDoble.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)