cmake_minimum_required(VERSION 3.16)

project(server LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)
file(GLOB BASEDEDATOS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/baseDeDatos/*.c)
file(GLOB LOGICA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/logica/*.c)
file(GLOB SERVIDOR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/servidor/*.c)

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${BASEDEDATOS_SRC} ${LOGICA_SRC} ${SERVIDOR_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SQLite3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC sockets cola listaSimple listaDoble tablaHash constantes protocolos SQLite3::SQLite3 sodium)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32)
endif()


get_filename_component(MINGW_BIN_DIR ${CMAKE_C_COMPILER} DIRECTORY)

set (SERVER_DLLS
libsodium-26.dll
libsqlite3-0.dll)

foreach(dll ${SERVER_DLLS})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MINGW_BIN_DIR}/${dll}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
endforeach()


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/database"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/database/schema.sql"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/database/schema.sql"
)