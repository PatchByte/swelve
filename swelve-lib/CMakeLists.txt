cmake_minimum_required (VERSION 3.8)
project("swelveLib")

option(SWELVE_LIB_ENABLE_WRITE "Enable's the Development utils")

file(GLOB SwelveLibFiles
    "include/*.hpp"
    "source/*.cpp"
)

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(${PROJECT_NAME} STATIC ${SwelveLibFiles})
add_library(lib::swelve ALIAS ${PROJECT_NAME})