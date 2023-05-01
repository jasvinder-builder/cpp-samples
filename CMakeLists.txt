cmake_minimum_required(VERSION 3.10)

project(Producer-Consumer)

set(CMAKE_CXX_STANDARD 11)

add_executable(Producer-Consumer producer-consumer/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(Producer-Consumer ${CMAKE_THREAD_LIBS_INIT})
