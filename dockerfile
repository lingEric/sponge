FROM ubuntu:22.04
ENV TARGET_APP=server

RUN apt update
RUN apt install -y libmysqlcppconn-dev librdkafka-dev build-essential cmake \
libssl-dev zlib1g-dev libboost-dev libboost-program-options-dev libzookeeper-mt-dev


RUN mkdir -p /sponge
COPY . /sponge

# build cppkafka
RUN mkdir -p /sponge/dependencies/cppkafka/build
RUN rm -rf /sponge/dependencies/cppkafka/build/*
WORKDIR /sponge/dependencies/cppkafka/build
RUN cmake -DCPPKAFKA_DISABLE_EXAMPLES=ON -DCPPKAFKA_DISABLE_TESTS=ON ..
RUN make -j2
RUN make install

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
WORKDIR /sponge/build
RUN cmake -DCMAKE_BUILD_TYPE=release -DSPONGE_DISABLE_EXAMPLES=ON -DSPONGE_DISABLE_TESTS=ON ..
RUN make -j2

WORKDIR /sponge
RUN chmod +x /sponge/entrypoint.sh
ENTRYPOINT ["/sponge/entrypoint.sh"]
# CMD ["/bin/bash", "-i"]
