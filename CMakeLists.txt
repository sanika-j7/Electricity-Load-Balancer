cmake_minimum_required(VERSION 3.15)
project(SmartGridSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Name the executable SmartGridSystem
add_executable(SmartGridSystem ${SOURCES})

# Force executable into build/ (no bin/, no Debug/Release)
set_target_properties(SmartGridSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
)
