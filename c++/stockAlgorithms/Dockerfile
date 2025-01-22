FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    cmake \
    libasio-dev \
    libeigen3-dev \
    nlohmann-json3-dev \
    git && apt clean \
    && mv /usr/include/eigen3/Eigen /usr/local/include/Eigen

RUN git clone --recurse-submodules -b v1.57.0 https://github.com/grpc/grpc && \
    cd grpc && \
    mkdir cmake/build && \
    cd cmake/build && \
    cmake -DCMAKE_INSTALL_PREFIX=/usr/local ../.. && \
    make -j 4 && \
    make install

WORKDIR /app

COPY stockAlgorithms /app/service

RUN cd service && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 8082

RUN ./service/build/stockAlgorithmsTest
CMD ["./service/build/stockAlgorithms"]