FROM debian:12.10-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    autoconf \
    libtool \
    pkg-config \
    cmake \
    libasio-dev \
    sqlite3 \
    libsqlite3-dev \
    git && apt clean
    
RUN cd /usr/local/include && \
    git clone https://github.com/CrowCpp/Crow.git && \
    cd Crow && \
    mkdir build && \
    cd build && \
    cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && \
    make install

RUN git clone --recurse-submodules -b v1.57.0 https://github.com/grpc/grpc && \
    cd grpc && \
    mkdir cmake/build && \
    cd cmake/build && \
    cmake \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        -DgRPC_INSTALL=ON \
        -DgRPC_BUILD_TESTS=OFF \
        -DgRPC_BUILD_CSHARP_EXT=OFF \
        -DgRPC_BUILD_GRPC_CPP_PLUGIN=ON \
        -DgRPC_BUILD_GRPC_CSHARP_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_NODE_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_PHP_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_PYTHON_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_RUBY_PLUGIN=OFF \
        -DCMAKE_BUILD_TYPE=Release \
    ../.. && \
    make -j$(nproc) && \
    make install

WORKDIR /app

COPY stockAggregatesStore /app/service
COPY sqlUtils /app/sqlUtils

RUN cd service && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 8080

CMD ["./service/build/stockAggregatesStore"]