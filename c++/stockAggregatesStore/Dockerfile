FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    cmake \
    libasio-dev \
    git
    
RUN apt update && apt install -y software-properties-common && \
    add-apt-repository ppa:deadsnakes/ppa && \
    apt install -y python3.11

RUN cd /usr/local/include && \
    git clone https://github.com/CrowCpp/Crow.git && \
    cd Crow && \
    mkdir build && \
    cd build && \
    cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && \
    make install


WORKDIR /app

COPY stockAggregatesStore /app/service
COPY sqlUtils /app/sqlUtils

RUN cd sqlUtils && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    cmake --build .

RUN cd service && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    cmake --build .

# EXPOSE 8080

CMD ["./service/build/StockAggregatesStore"]