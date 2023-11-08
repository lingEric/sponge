FROM ubuntu:22.04
ENV TARGET_APP=server

RUN apt update
RUN apt install -y build-essential cmake libmysqlcppconn-dev


RUN mkdir -p /sponge
COPY . /sponge

# build muduo
RUN mkdir -p /sponge/dependencies/muduo/build
RUN rm -rf /sponge/dependencies/muduo/build/*
WORKDIR /sponge/dependencies/muduo/build
RUN cmake -DMUDUO_BUILD_EXAMPLES=OFF ..
RUN make -j2
RUN make install

# build hiredis
RUN mkdir -p /sponge/dependencies/hiredis/build
RUN rm -rf /sponge/dependencies/hiredis/build/*
WORKDIR /sponge/dependencies/hiredis/build
RUN cmake ..
RUN make -j2
RUN make install

# build redis-plus-plus
RUN mkdir -p /sponge/dependencies/redis-plus-plus/build
RUN rm -rf /sponge/dependencies/redis-plus-plus/build/*
WORKDIR /sponge/dependencies/redis-plus-plus/build
RUN cmake -DREDIS_PLUS_PLUS_CXX_STANDARD=11 -DREDIS_PLUS_PLUS_BUILD_STATIC=OFF -DREDIS_PLUS_PLUS_BUILD_TEST=OFF ..
RUN make -j2
RUN make install

# build sponge
RUN mkdir -p /sponge/build
RUN rm -rf /sponge/build/*
RUN rm -rf /sponge/bin/*
WORKDIR /sponge/build
RUN cmake -DCMAKE_BUILD_TYPE=release -DSPONGE_DISABLE_EXAMPLES=ON -DSPONGE_DISABLE_TESTS=ON ..
# RUN cmake -DCMAKE_BUILD_TYPE=release ..
RUN make -j2

# 修改容器中的数据库ip地址
RUN sed -i 's/localhost/mysql/g' /sponge/bin/mysql.cnf
RUN sed -i 's/localhost/redis/g' /sponge/bin/redis.cnf

WORKDIR /sponge/bin
RUN chmod +x /sponge/entrypoint.sh
ENTRYPOINT ["/sponge/entrypoint.sh"]
# CMD ["/bin/bash", "-i"]
