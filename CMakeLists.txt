cmake_minimum_required (VERSION 3.8)
project("build")


set(CMAKE_BINARY_DIR "/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SWELVE_ENABLE_TEST "Enable Swelve Tests" OFF)

add_subdirectory("swelve-lib")

if(SWELVE_ENABLE_TEST)
    add_subdirectory("swelve-tests")
endif(SWELVE_ENABLE_TEST)