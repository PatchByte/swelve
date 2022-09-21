cmake_minimum_required (VERSION 3.8)
project("swelveTest")

file(GLOB SwelveTestFiles
    "source/*"
)

add_executable(${PROJECT_NAME} ${SwelveTestFiles})

target_link_libraries(${PROJECT_NAME} lib::swelve)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})