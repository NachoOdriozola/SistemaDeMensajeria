cmake_minimum_required(VERSION 3.16)

project(client LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

file (GLOB COMUNICACION_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/comunicacion/*.c)
file (GLOB LOGICA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/logica/*.c)

file(GLOB INTERFAZAUTENTICACION_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazAutenticacion/*.c)
file(GLOB INTERFAZCONTACTOS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazContactos/*.c)
file(GLOB INTERFAZREGISTRO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/interfazRegistro/*.c)

file(GLOB RECURSOSCOMUNESAUTENTICACIONREGISTRO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/interfacesGraficas/recursosComunes/AutenticacionRegistro/*.c)

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${COMUNICACION_SRC} ${LOGICA_SRC} ${INTERFAZAUTENTICACION_SRC} ${INTERFAZCONTACTOS_SRC} ${INTERFAZREGISTRO_SRC} ${RECURSOSCOMUNESAUTENTICACIONREGISTRO_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC sockets listaDoble constantes protocolos ws2_32 csfml-system csfml-window csfml-graphics)


get_filename_component(MINGW_BIN_DIR ${CMAKE_C_COMPILER} DIRECTORY)

set (CLIENT_DLLS
libcsfml-graphics-3.dll
libcsfml-window-3.dll
libgcc_s_seh-1.dll
libsfml-graphics-3.dll
libstdc++-6.dll
libsfml-system-3.dll
libsfml-window-3.dll
libwinpthread-1.dll
libfreetype-6.dll
libbrotlidec.dll
libbz2-1.dll
libharfbuzz-0.dll
zlib1.dll
libpng16-16.dll
libbrotlicommon.dll
libglib-2.0-0.dll
libgraphite2.dll
libintl-8.dll
libiconv-2.dll
libpcre2-8-0.dll
)

foreach(dll ${CLIENT_DLLS})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MINGW_BIN_DIR}/${dll}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
endforeach()


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)