cmake_minimum_required(VERSION 3.16)

project(client LANGUAGES C)

file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

file (GLOB COMUNICACION_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/comunicacion/*.c)
file (GLOB LOGICA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/logica/*.c)

file(GLOB INTERFAZAUTENTICACION_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazAutenticacion/*.c)
file(GLOB INTERFAZCONTACTOS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazContactos/*.c)
file(GLOB INTERFAZREGISTRO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazRegistro/*.c)

file(GLOB RECURSOSCOMUNESAUTENTICACIONREGISTRO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/recursosComunes/AutenticacionRegistro/*.c)

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${COMUNICACION_SRC} ${LOGICA_SRC} ${INTERFAZAUTENTICACION_SRC} ${INTERFAZCONTACTOS_SRC} ${INTERFAZREGISTRO_SRC} ${RECURSOSCOMUNESAUTENTICACIONREGISTRO_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME} PUBLIC sockets listaDoble constantes protocolos ws2_32 csfml-system csfml-window csfml-graphics)

file (GLOB DLLS "${CMAKE_CURRENT_SOURCE_DIR}/../external/csfml/bin/*.dll")
add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DLLS} "$<TARGET_FILE_DIR:${PROJECT_NAME}>")