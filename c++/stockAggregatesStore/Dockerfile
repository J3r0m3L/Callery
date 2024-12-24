FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    cmake

WORKDIR /app

COPY stockAggregatesStore /app/service
COPY sqlUtils /app/sqlUtils

RUN cd service && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    cmake --build .

# EXPOSE 8080

CMD ["./service/build/StockAggregatesStore"]