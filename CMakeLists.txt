cmake_minimum_required(VERSION 3.17)
project(yellower)

set(CMAKE_CXX_STANDARD 17)

include_directories(ExternalIncludeFiles)

add_executable(yellower main.cpp threaded_processors.cpp yellower.h)
