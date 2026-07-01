cmake_minimum_required(VERSION 3.16)

project(client LANGUAGES C)

file(GLOB CLIENT_SRC ${PROJECT_SOURCE_DIR}/src/*.c)

file(GLOB INTERFAZAUTENTICACION_SRC ${PROJECT_SOURCE_DIR}/src/interfacesGraficas/interfazAutenticacion/*.c)
file(GLOB INTERFAZCONFIG_SRC ${PROJECT_SOURCE_DIR}/src/interfacesGraficas/interfazConfig/*.c)
file(GLOB INTERFAZCONTACTOS_SRC ${PROJECT_SOURCE_DIR}/src/interfacesGraficas/interfazContactos/*.c)
file(GLOB INTERFAZREGISTRO_SRC ${PROJECT_SOURCE_DIR}/src/interfacesGraficas/interfazRegistro/*.c)
file(GLOB INTERFAZSALAS_SRC ${PROJECT_SOURCE_DIR}/src/interfacesGraficas/interfazSalas/*.c)

file(GLOB RECURSOSCOMUNESAUTENTICACIONREGISTRO_SRC ${PROJECT_SOURCE_DIR}/src/interfacesGraficas/recursosComunes/recursosComunesAutenticacionRegistro/*.c)
file(GLOB RECURSOSCOMUNESCONTACTOSSALAS_SRC ${PROJECT_SOURCE_DIR}/src/interfacesGraficas/recursosComunes/recursosComunesContactosSalas/*.c)

add_executable(${PROJECT_NAME} ${CLIENT_SRC} ${INTERFAZAUTENTICACION_SRC} ${INTERFAZCONFIG_SRC} ${INTERFAZCONTACTOS_SRC} ${INTERFAZREGISTRO_SRC} ${INTERFAZSALAS_SRC} ${RECURSOSCOMUNESAUTENTICACIONREGISTRO_SRC} ${RECURSOSCOMUNESCONTACTOSSALAS_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/interfacesGraficas/interfazAutenticacion ${PROJECT_SOURCE_DIR}/include/interfacesGraficas/interfazConfig ${PROJECT_SOURCE_DIR}/include/interfacesGraficas/interfazContactos ${PROJECT_SOURCE_DIR}/include/interfacesGraficas/interfazRegistro ${PROJECT_SOURCE_DIR}/include/interfacesGraficas/interfazSalas  ${PROJECT_SOURCE_DIR}/include/interfacesGraficas/recursosComunes/recursosComunesAutenticacionRegistro ${PROJECT_SOURCE_DIR}/include/interfacesGraficas/recursosComunes/recursosComunesContactosSalas ${PROJECT_SOURCE_DIR}/../external/csfml/include)

target_link_libraries(${PROJECT_NAME} PUBLIC nodo listaSimple listaCircular constantes protocolos ws2_32
                                ${PROJECT_SOURCE_DIR}/../external/csfml/lib/csfml-system.lib
                                ${PROJECT_SOURCE_DIR}/../external/csfml/lib/csfml-window.lib
                                ${PROJECT_SOURCE_DIR}/../external/csfml/lib/csfml-graphics.lib)