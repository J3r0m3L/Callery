FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    cmake

WORKDIR /stockAggregatesStore

COPY . /stockAggregatesStore/service
COPY ../sqlUtils /stockAggregatesStore/sqlUtils

EXPOSE 8080

CMD ["./build/service"]