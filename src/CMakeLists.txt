cmake_minimum_required(VERSION 3.10)

project(TEP VERSION 1.0)

configure_file(TEPConfig.h.in TEPConfig.h)

add_executable(${PROJECT_NAME} globant.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")