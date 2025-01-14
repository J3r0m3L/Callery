FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    cmake \
    libasio-dev \
    libeigen3-dev \
    git && apt clean \
    && mv /usr/include/eigen3/Eigen /usr/local/include/Eigen

RUN cd /usr/local/include && \
    git clone https://github.com/CrowCpp/Crow.git && \
    cd Crow && \
    mkdir build && \
    cd build && \
    cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && \
    make install

WORKDIR /app

COPY stockAlgorithms /app/service

RUN cd service && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 8082

CMD ["./service/build/stockAlgorithms"]