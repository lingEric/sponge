cmake_minimum_required(VERSION 3.10)
project(sponge C CXX)

# <---------- set c++ standard ------------->
# NOTE: you must build redis-plus-plus and your application code with the same standard.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# <------------ add hiredis dependency --------------->
find_path(HIREDIS_HEADER hiredis)
find_library(HIREDIS_LIB hiredis)

message("Found HIREDIS_HEADER: ${HIREDIS_HEADER}")
message("Found HIREDIS_LIB: ${HIREDIS_LIB}")
include_directories(${HIREDIS_HEADER})

# <------------ add redis-plus-plus dependency -------------->
# NOTE: this should be *sw* NOT *redis++*
find_path(REDIS_PLUS_PLUS_HEADER sw)
find_library(REDIS_PLUS_PLUS_LIB redis++)

message("Found REDIS_PLUS_PLUS_HEADER: ${REDIS_PLUS_PLUS_HEADER}")
message("Found REDIS_PLUS_PLUS_LIB: ${REDIS_PLUS_PLUS_LIB}")
include_directories(${REDIS_PLUS_PLUS_HEADER})

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
