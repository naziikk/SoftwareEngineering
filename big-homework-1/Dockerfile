FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libpq-dev \
    libcurl4-openssl-dev \
    g++ \
    wget \
    python3 \
    python3-pip \
    git \
    && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/jtv/libpqxx/archive/refs/tags/7.7.5.tar.gz && \
    tar -xvzf 7.7.5.tar.gz && \
    cd libpqxx-7.7.5 && \
    cmake -B build . && \
    cmake --build build --target install && \
    cd .. && rm -rf libpqxx-7.7.5 7.7.5.tar.gz

WORKDIR /app

COPY . .

RUN apt-get update && apt-get install -y software-properties-common
RUN apt-get remove -y cmake && apt-get purge -y cmake
RUN wget -qO- "https://cmake.org/files/v3.27/cmake-3.27.0-linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local

RUN rm -rf build CMakeFiles CMakeCache.txt cmake_install.cmake

RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make

CMD ["./build/big-homework-1"]

EXPOSE 8002