cmake_minimum_required(VERSION 3.21)

project(InputsViewer LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Geode SDK root (usually set by the CLI / workflow)
# If you already have this set elsewhere, you can remove or adjust.
if(NOT DEFINED GEODE_SDK)
    message(FATAL_ERROR "GEODE_SDK is not set")
endif()

# Add main source files
file(GLOB_RECURSE INPUTS_VIEWER_SOURCES
    src/*.cpp
    src/class/*.cpp
)

add_library(InputsViewer SHARED
    ${INPUTS_VIEWER_SOURCES}
)

# Include dirs – THIS fixes the iOS header issue
target_include_directories(InputsViewer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/class
)

# Link against Geode (loader, bindings, etc.)
# These are typical for Geode mods; adjust if your SDK layout differs.
target_link_libraries(InputsViewer PRIVATE
    geode-sdk::loader
    geode-sdk::bindings
)

# Recommended compile options for Geode mods
if(APPLE)
    # iOS / macOS specific flags
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

# Install / output config (Geode usually handles this via CLI/workflow,
# so you might not need anything extra here)
