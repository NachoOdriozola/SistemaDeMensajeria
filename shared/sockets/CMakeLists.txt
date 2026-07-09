cmake_minimum_required(VERSION 3.16)

project(sockets LANGUAGES C)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/sockets_windows.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)