cmake_minimum_required(VERSION 3.16)

project(HotelMini LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(HotelMini main.cpp ${SRC})

target_include_directories(HotelMini PRIVATE ${CMAKE_SOURCE_DIR}/src)

if (NOT MSVC)
    target_link_libraries(HotelMini PRIVATE stdc++fs)
endif()