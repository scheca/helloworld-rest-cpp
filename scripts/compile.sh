#!/bin/bash

# compile
docker run \
    --rm \
    -it \
    -v $PWD:/app \
    -w /app \
    scheca/gcc-cmake-lcov:gcc-10 \
    sh -c '(test -d build || mkdir build) && cd build && cmake .. && make -j$(nproc)'
