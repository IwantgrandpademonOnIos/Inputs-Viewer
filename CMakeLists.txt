cmake_minimum_required(VERSION 3.21)

project(InputsViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Geode REQUIRED)

file(GLOB_RECURSE INPUTS_VIEWER_SOURCES
    src/*.cpp
    src/class/*.cpp
)

add_library(InputsViewer SHARED
    ${INPUTS_VIEWER_SOURCES}
)

target_include_directories(InputsViewer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/class
)

target_link_libraries(InputsViewer PRIVATE
    geode::loader
    geode::bindings
)

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

geode_mod(InputsViewer)
