aux_source_directory(${CMAKE_SOURCE_DIR}/src/database/mysql/ MYSQL_SOURCE_FILES)

message("MySQL源文件 ${MYSQL_SOURCE_FILES}")

# 数据库连接池的性能测试
add_executable(benchmark benchmark.cpp ${MYSQL_SOURCE_FILES} ${MYSQL_SOURCE_FILES} ${CMAKE_SOURCE_DIR}/src/log/logger.cc)


target_link_libraries(benchmark mysqlcppconn)