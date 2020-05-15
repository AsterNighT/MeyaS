cmake_minimum_required(VERSION 3.16)
project(MeyaS)

set(CMAKE_CXX_STANDARD 14)
aux_source_directory(./src MAIN_LIST)
include_directories(./include)

add_library(MeyaS STATIC ${MAIN_LIST})
add_executable(Client test/client.cpp)
add_executable(Server test/server.cpp)

link_directories(.)

ADD_DEFINITIONS(-DDEBUG_MeyaS)
target_link_libraries(MeyaS Ws2_32.lib)
target_link_libraries(Client MeyaS)
target_link_libraries(Server MeyaS)