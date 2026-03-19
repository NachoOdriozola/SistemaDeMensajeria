cmake_minimum_required(VERSION 3.16)

add_library(csfml-system STATIC IMPORTED)
set_target_properties(csfml-system PROPERTIES
    IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/csfml-system.lib
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
)

add_library(csfml-window STATIC IMPORTED)
set_target_properties(csfml-window PROPERTIES
    IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/csfml-window.lib
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
)

add_library(csfml-graphics STATIC IMPORTED)
set_target_properties(csfml-graphics PROPERTIES
    IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/csfml-graphics.lib
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
)