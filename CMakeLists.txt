cmake_minimum_required(VERSION 3.10)

project(TEP VERSION 1.0)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/TEPConfig.h.in TEPConfig.h)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/globant.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")