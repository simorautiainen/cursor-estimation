cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DROOT_PATH="${CMAKE_SOURCE_DIR}")

find_package(Eigen3 REQUIRED)

project(CursorPredict)

add_subdirectory(velocitydemo)
add_subdirectory(lib)