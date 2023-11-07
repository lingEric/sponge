aux_source_directory(${CMAKE_SOURCE_DIR}/src/database/mysql/ MYSQL_SOURCE_FILES)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/log/ Log_SOURCE_FILES)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/model/ MODEL_SOURCE_FILES)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/service/ SERVICE_SOURCE_FILES)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/server/ SERVER_SOURCE_FILES)



add_executable(server ${MYSQL_SOURCE_FILES} ${Log_SOURCE_FILES} ${MODEL_SOURCE_FILES} ${SERVICE_SOURCE_FILES} ${SERVER_SOURCE_FILES})
target_link_libraries(server ${MUDUO_NET_LIB} ${MUDUO_BASE_LIB} mysqlcppconn)