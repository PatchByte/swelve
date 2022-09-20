cmake_minimum_required (VERSION 3.8)
project("swelveTest")

file(GLOB SwelveTestFiles
    "source/*"
)

add_executable(${PROJECT_NAME} ${SwelveTestFiles})