cmake_minimum_required(VERSION 3.16)
project(PlantCareApp LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include Headers
include_directories(include)

# Detect Dependencies
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(SQLite3 REQUIRED)

# Enable Qt's meta-object compiler
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Source files
set(PROJECT_SOURCES
	src/main.cxx
	src/plant.cxx
	src/mainWindow.cxx
	src/secondWindow.cxx
	src/cardtemplate.cxx
	src/editwindow.cxx
)

# Header Files
set(HEADER_SOURCES
	include/main.hxx
	include/plant.hxx
	include/mainWindow.hxx
	include/secondWindow.hxx
	include/cardtemplate.hxx
	include/editwindow.hxx
)

# UI Files
set(UI_SOURCES
	ui/mainWindow.ui
	ui/secondWindow.ui
	ui/cardtemplate.ui
	ui/editwindow.ui
)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

# Define the executable
qt_add_executable(PlantCareApp MANUAL_FINALIZATION ${PROJECT_SOURCES} ${HEADER_SOURCES} ${UI_SOURCES})

# Link Dependency Libraries
target_link_libraries(PlantCareApp PRIVATE Qt6::Widgets)
target_include_directories(PlantCareApp PRIVATE ${SQLite3_INCLUDE_DIRS})
target_link_libraries(PlantCareApp PRIVATE ${SQLite3_LIBRARIES})

# Compiler warnings
target_compile_options(PlantCareApp PRIVATE -Wall -Wextra -O2)

# Include Debug Symbols
set(CMAKE_BUILD_TYPE Debug)

# Finalize qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PlantCareApp)
endif()
