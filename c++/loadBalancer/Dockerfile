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


RUN cd /usr/local/include && \
    git clone https://github.com/yhirose/cpp-httplib.git && \
    cd cpp-httplib && \
    mkdir build && \
    cd build && \
    cmake .. && \
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