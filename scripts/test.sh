#!/bin/bash

docker run \
    --rm \
    -it \
    -v $PWD:/app \
    -w /app \
    scheca/gcc-cmake-lcov:gcc-10 \
    sh -c 'make test -C build/external/Build/server'