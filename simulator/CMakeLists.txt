cmake_minimum_required(VERSION 3.10)
project(OCPP_Simulator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/ixwebsocket)

add_executable(ocpp_sim main.cpp)
target_link_libraries(ocpp_sim ixwebsocket)
