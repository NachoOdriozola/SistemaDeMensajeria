cmake_minimum_required(VERSION 3.16)

project(server LANGUAGES C)

file(GLOB SERVIDOR_SRC ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${SERVIDOR_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC nodo listaSimple tablaHash constantes protocolos ws2_32 sqlite3)