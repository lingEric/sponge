add_executable(testredis testredis.cpp)
target_link_libraries(testredis ${HIREDIS_LIB} ${REDIS_PLUS_PLUS_LIB})