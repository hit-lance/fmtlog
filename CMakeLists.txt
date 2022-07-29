cmake_minimum_required(VERSION 3.10)

project(fmtlog CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_BUILD_TYPE "Debug")

find_package(fmt)

add_executable(main main.cpp)
target_link_libraries(main fmt::fmt)
