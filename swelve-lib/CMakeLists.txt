cmake_minimum_required (VERSION 3.8)
project("swelveLib")

file(GLOB SwelveLibFiles
    "include/*"
    "source/*"
)

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(${PROJECT_NAME} STATIC ${SwelveLibFiles})
add_library(lib::swelve ALIAS ${PROJECT_NAME})