cmake_minimum_required(VERSION 3.10)
project(sponge C CXX)
option(SPONGE_DISABLE_EXAMPLES "Disable build of sponge examples." OFF)
option(SPONGE_DISABLE_TESTS "Disable build of sponge tests." OFF)

# <------------ copy configuration file to bin --------------->
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Set the source directory of your configuration files
# set(CONFIG_FILES
#     ${PROJECT_SOURCE_DIR}/config_file1.txt
#     ${PROJECT_SOURCE_DIR}/config_file2.txt
#     ${PROJECT_SOURCE_DIR}/config_file3.txt
# )

# Set the destination directory of your configuration files in the build directory
# set(CONFIG_FILES_DESTINATION ${PROJECT_SOURCE_DIR}/bin)

# Copy the configuration files from the source directory to the build directory
# file(COPY ${CONFIG_FILES} DESTINATION ${CONFIG_FILES_DESTINATION})



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

# <------------ add cppkafka dependency --------------->
find_package(CppKafka REQUIRED)

# <------------ add boost dependency --------------->
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})



include_directories(thirdparty)
include_directories(src/include)
include_directories(src/include/database)
include_directories(src/include/database/mysql)
include_directories(src/include/database/sqlite)
include_directories(src/include/log)
include_directories(src/include/model)
include_directories(src/include/threadpool)
include_directories(src/include/server)


add_subdirectory(src)
# Add the example subdirectory if the option is not disabled
if (NOT SPONGE_DISABLE_EXAMPLES)
    add_subdirectory(example)
endif()

# Add the test subdirectory if the option is not disabled
if (NOT SPONGE_DISABLE_TESTS)
    add_subdirectory(test)
endif()
