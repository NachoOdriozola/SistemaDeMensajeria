cmake_minimum_required(VERSION 3.16)

project(server LANGUAGES C)

file(GLOB SERVIDOR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${SERVIDOR_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC listaDoble tablaHash constantes protocolos ws2_32 sqlite3 sodium)