cmake_minimum_required(VERSION 3.16)

project(client LANGUAGES C)

file(GLOB CLIENT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

file(GLOB INTERFAZAUTENTICACION_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazAutenticacion/*.c)
file(GLOB INTERFAZCONFIG_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazConfig/*.c)
file(GLOB INTERFAZCONTACTOS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazContactos/*.c)
file(GLOB INTERFAZREGISTRO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazRegistro/*.c)
file(GLOB INTERFAZSALAS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazSalas/*.c)

file(GLOB RECURSOSCOMUNESAUTENTICACIONREGISTRO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/recursosComunes/recursosComunesAutenticacionRegistro/*.c)
file(GLOB RECURSOSCOMUNESCONTACTOSSALAS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/recursosComunes/recursosComunesContactosSalas/*.c)

add_executable(${PROJECT_NAME} ${CLIENT_SRC} ${INTERFAZAUTENTICACION_SRC} ${INTERFAZCONFIG_SRC} ${INTERFAZCONTACTOS_SRC} ${INTERFAZREGISTRO_SRC} ${INTERFAZSALAS_SRC} ${RECURSOSCOMUNESAUTENTICACIONREGISTRO_SRC} ${RECURSOSCOMUNESCONTACTOSSALAS_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/interfacesGraficas/interfazAutenticacion ${CMAKE_CURRENT_SOURCE_DIR}/include/interfacesGraficas/interfazConfig ${CMAKE_CURRENT_SOURCE_DIR}/include/interfacesGraficas/interfazContactos ${CMAKE_CURRENT_SOURCE_DIR}/include/interfacesGraficas/interfazRegistro ${CMAKE_CURRENT_SOURCE_DIR}/include/interfacesGraficas/interfazSalas  ${CMAKE_CURRENT_SOURCE_DIR}/include/interfacesGraficas/recursosComunes/recursosComunesAutenticacionRegistro ${CMAKE_CURRENT_SOURCE_DIR}/include/interfacesGraficas/recursosComunes/recursosComunesContactosSalas ${CMAKE_CURRENT_SOURCE_DIR}/../external/csfml/include)

target_link_libraries(${PROJECT_NAME} PUBLIC listaDoble constantes protocolos ws2_32 csfml-system csfml-window csfml-graphics)

