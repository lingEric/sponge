cmake_minimum_required(VERSION 3.10)
project(sponge C CXX)


include_directories(include)
include_directories(thirdparty)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)
