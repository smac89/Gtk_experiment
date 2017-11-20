cmake_minimum_required(VERSION 2.8)
project(Gtkmm_experiment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(include ${GTKMM_INCLUDE_DIRS})

file(GLOB_RECURSE PROJECT_SOURCES
        include/*.hpp
        src/*.cpp)

set(SOURCE_FILES ${PROJECT_SOURCES} main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})
add_definitions(
        -DGTK_DISABLE_SINGLE_INCLUDES
        -DGDK_DISABLE_DEPRECATED
        -DGTK_DISABLE_DEPRECATED)
