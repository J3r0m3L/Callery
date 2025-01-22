FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    cmake \
    libasio-dev \
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
    cmake -DCMAKE_INSTALL_PREFIX=/usr/local ../.. && \
    make -j 4 && \
    make install

WORKDIR /app

COPY loadBalancer /app/service

RUN cd service && \
    mkdir -p build && \ 
    cd build && \
    cmake .. && \
    make

EXPOSE 8081

CMD ["./service/build/loadBalancer"]