cmake_minimum_required(VERSION 3.16)
project(PlantCareApp LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directory
include_directories(include)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Enable Qt's meta-object compiler
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Source files
file(GLOB_RECURSE SOURCES src/*.cxx)

# Define the executable
add_executable(PlantCareApp ${SOURCES})

# Link Qt6
target_link_libraries(PlantCareApp PRIVATE Qt6::Widgets)

# Compiler warnings
target_compile_options(PlantCareApp PRIVATE -Wall -Wextra -O2)

# Include Debug Symbols
set(CMAKE_BUILD_TYPE Debug)
