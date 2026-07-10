cmake_minimum_required(VERSION 3.21)

project(InputsViewer LANGUAGES CXX)

find_package(Geode REQUIRED)

geode_mod(InputsViewer)

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/InputsViewer.cpp
    src/InputsViewerLayer.cpp
)
