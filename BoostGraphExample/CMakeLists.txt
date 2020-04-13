cmake_minimum_required(VERSION 3.15)
project(BoostGraphExample)

set(CMAKE_CXX_STANDARD 14)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(BoostGraphExample main.cpp Node.cpp Node.h CustomNodeExample.cpp ShortestPathExample.cpp)
target_link_libraries(BoostGraphExample -static)
target_link_libraries(BoostGraphExample ${Boost_LIBRARIES})