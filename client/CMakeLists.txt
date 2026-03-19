cmake_minimum_required(VERSION 3.16)

project(client LANGUAGES C)

file(GLOB CLIENT_SRC ${PROJECT_SOURCE_DIR}/src/*.c)

file(GLOB INTERFACES_SRC ${PROJECT_SOURCE_DIR}/src/interfaces/*.c)

file(GLOB RECURSOSGRAFICOSCOMUNES_SRC ${PROJECT_SOURCE_DIR}/src/recursosGraficosComunes/*.c)

add_executable(${PROJECT_NAME} ${CLIENT_SRC} ${INTERFACES_SRC} ${RECURSOSGRAFICOSCOMUNES_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/interfaces ${PROJECT_SOURCE_DIR}/include/recursosGraficosComunes ${PROJECT_SOURCE_DIR}/../external/csfml/include)

target_link_libraries(${PROJECT_NAME} PUBLIC nodo listaSimple listaCircular constantes protocolos ws2_32
                                ${PROJECT_SOURCE_DIR}/../external/csfml/lib/csfml-system.lib
                                ${PROJECT_SOURCE_DIR}/../external/csfml/lib/csfml-window.lib
                                ${PROJECT_SOURCE_DIR}/../external/csfml/lib/csfml-graphics.lib)