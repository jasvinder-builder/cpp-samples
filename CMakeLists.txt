cmake_minimum_required(VERSION 3.10)

project(Cpp-samples)

set(CMAKE_CXX_STANDARD 11)

add_executable(producer-consumer producer-consumer/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(producer-consumer ${CMAKE_THREAD_LIBS_INIT})

add_executable(async async/main.cpp)

add_executable(promise promise/main.cpp)
