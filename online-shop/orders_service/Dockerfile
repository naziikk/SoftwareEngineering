FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libpq-dev \
    libcurl4-openssl-dev \
    g++ \
    wget \
    libssl-dev \
    git \
    pkg-config \
    libboost-system-dev \
    libboost-thread-dev \
    librdkafka-dev \
    zlib1g-dev && \
    rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/jtv/libpqxx/archive/refs/tags/7.7.5.tar.gz && \
    tar -xvzf 7.7.5.tar.gz && \
    cd libpqxx-7.7.5 && \
    cmake -B build . && \
    cmake --build build --target install && \
    cd .. && rm -rf libpqxx-7.7.5 7.7.5.tar.gz

RUN git clone https://github.com/mfontanini/cppkafka.git && \
    cd cppkafka && mkdir build && cd build && \
    cmake .. && \
    make -j4 && make install && \
    cd ../.. && rm -rf cppkafka

WORKDIR /app

COPY . .

RUN rm -rf build && mkdir -p build && cd build && \
    cmake .. && \
    make VERBOSE=1

CMD ["bash", "-c", "./build/OrdersService"]

EXPOSE 8007