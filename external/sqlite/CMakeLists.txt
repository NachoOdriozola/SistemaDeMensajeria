cmake_minimum_required(VERSION 3.16)

project(sqlite3 LANGUAGES C)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/sqlite3.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)