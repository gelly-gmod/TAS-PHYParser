cmake_minimum_required(VERSION 3.20)

project("PHYParser" CXX)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_CXX_STANDARD 20)

add_library(PHYParser
        src/phy.hpp
        PHYParser.hpp
)

target_include_directories(
        PHYParser PRIVATE
        "src"
)
