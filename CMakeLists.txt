cmake_minimum_required(VERSION 3.10)
project(sponge C CXX)


include_directories(thirdparty)
include_directories(src/include)
include_directories(src/include/database)
include_directories(src/include/database/mysql)
include_directories(src/include/database/sqlite)
include_directories(src/include/log)
include_directories(src/include/model)


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)
