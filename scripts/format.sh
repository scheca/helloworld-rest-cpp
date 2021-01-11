#!/bin/bash

find src/ \( -iname *.h -o -iname *.cc \) -exec \
  docker run \
      --rm \
      -v $PWD:/app \
      -w /app \
      unibeautify/clang-format -i \
  {} +