cmake_minimum_required(VERSION 3.16)

project(server LANGUAGES C)

file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)
file(GLOB BASEDEDATOS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/baseDeDatos/*.c)
file(GLOB LOGICA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/logica/*.c)
file(GLOB SERVIDOR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/servidor/*.c)

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${BASEDEDATOS_SRC} ${LOGICA_SRC} ${SERVIDOR_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC sockets cola listaSimple listaDoble tablaHash constantes protocolos ws2_32 sqlite3 sodium)