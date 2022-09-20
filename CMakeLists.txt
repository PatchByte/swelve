cmake_minimum_required (VERSION 3.8)
project("build")


set(CMAKE_BINARY_DIR "/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("swelve-lib")
add_subdirectory("swelve-tests")