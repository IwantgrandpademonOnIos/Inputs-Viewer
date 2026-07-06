cmake_minimum_required(VERSION 3.21)

project(InputsViewer LANGUAGES CXX)

# Modern C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Geode SDK (provided automatically by CLI / GitHub Actions)
find_package(Geode REQUIRED)

# Collect all source files
file(GLOB_RECURSE INPUTS_VIEWER_SOURCES
    src/*.cpp
    src/class/*.cpp
)

# Create the mod target
add_library(InputsViewer SHARED
    ${INPUTS_VIEWER_SOURCES}
)

# Include directories — REQUIRED for iOS to find headers
target_include_directories(InputsViewer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/class
)

# Link against Geode loader + bindings
target_link_libraries(InputsViewer PRIVATE
    geode::loader
    geode::bindings
)

# Platform-specific tweaks
if(APPLE)
    target_compile_options(InputsViewer PRIVATE
        -fvisibility=hidden
        -ffunction-sections
        -fdata-sections
    )
elseif(WIN32)
    target_compile_definitions(InputsViewer PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif

# Register the mod with Geode
geode_mod(InputsViewer)
