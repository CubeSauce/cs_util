cmake_minimum_required(VERSION 3.5...4.0)

project(cs_util VERSION 0.0.1 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE sources
    src/**.cpp
)

add_library(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_sources(${PROJECT_NAME} PUBLIC ${sources})

enable_testing()
add_subdirectory(tests)
