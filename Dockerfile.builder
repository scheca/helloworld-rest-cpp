FROM rikorose/gcc-cmake:gcc-10

RUN git clone https://github.com/linux-test-project/lcov.git \
      && make install -C lcov \
      && rm -rf lcov
