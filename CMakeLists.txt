cmake_minimum_required(VERSION 3.17)
project(spl)

set(CMAKE_CXX_STANDARD 11)

add_executable(spl src/main.cpp src/Agent.cpp src/Graph.cpp src/Session.cpp src/Tree.cpp)