# Dockerized Hello-World with Drogon

This project intends to be a skeleton for REST services written in C++.
Probably C=+ is not the best choice for this kind of projects,
but it's been fun to construct such a cumbersome project.

As a practical utility, if you're a C++ programmer, and you're applying
for a web developer position, you may see this project as an inspiration
for your code challenge.

It uses [drogon], a _C++14/17-based HTTP application framework_.
The application code uses [spdlog] because it's easy to use and extend with
your custom logging backends.

The full dependency tree is:

```
                           ┌────────────┐
                           │            │
                           │     app    │
                           │            │
                           └──────┬─────┘
                                  │
                                  │
                                  │
        ┌─────────────────────────┼───────────────────────────┐
        │                         │                           │
        │                         │                           │
        │                         │                           │
 ┌──────▼─────┐            ┌──────▼─────┐              ┌──────▼─────┐
 │            │            │            │              │            │
 │   spdlog   │            │   drogon   │              │    gtest   │
 │            │            │            │              │            │
 └────────────┘            └──────┬─────┘              └────────────┘
                                  │
                                  │
                                  │
        ┌─────────────────────────┼───────────────────────────┐
        │                         │                           │
        │                         │                           │
        │                         │                           │
 ┌──────▼─────┐            ┌──────▼─────┐              ┌──────▼─────┐
 │            │            │            │              │            │
 │   c-ares   │            │  jsoncpp   │              │   brotli   │
 │            │            │            │              │            │
 └────────────┘            └────────────┘              └────────────┘
```

## Build system

Tools used by the project:

- cmake
- g++
- lcov
- clang-format

We're using a custom docker image based on `rikorose/gcc-cmake:gcc-10`,
plus `lcov` installed on top. This image can be built like this:

```shell
docker build -t scheca/gcc-cmake-lcov:gcc-10 -f Dockerfile.builder .
```

__Note__: you can tag your image as you wish, but remember to adapt the scripts
inside the `scripts` directory.

The provided `Makefile` is just a toolset to simplify the development cycle.  
It also helps set up an eventual CI pipeline.

The build system produces an out of source build inside the `build` directory.

- `make compile` downloads (if not yet) and builds the dependencies, then builds the app.
- `make build` builds an image with the server artifact binary.
   - you can tweak the `build.sh` script to give the image the tag of your choice. 
    
At this point, the server can be started with:

```shell
$ make run
[I] [18:06:46 +00:00] [thread 8] Starting hello-world server on port 8080
```

You can cURL the server from another console:

```shell
$ curl -v localhost:8080/status
...
< HTTP/1.1 200 OK
< content-length: 0
< content-type: text/html; charset=utf-8
< server: drogon/1.7.0
< date: Sun, 20 Jun 2021 17:41:54 GMT
...
```

```shell
$ curl -s -H "content-type:application/json" localhost:8080/greet -d '{"greeting":"hi server!"}'
...
< HTTP/1.1 200 OK
< content-length: 48
< content-type: application/json; charset=utf-8
< server: drogon/1.7.0
< date: Sun, 20 Jun 2021 18:02:43 GMT
...
{"response": "Hi there!, you told me: hi server!"}
```

## Application structure

The app code sits under `/src`, where there is a folder for the API and service layers.
Each of these components have their unit tests sitting along with them.

There is algo a `log` subfolder which initializes and provides a unique instance of a logger.

## Testing

```shell
$ make test
...
100% tests passed, 0 tests failed out of 5

Total Test time (real) =   0.47 sec
...
```

### Code coverage

It runs the tests plus generates a HTML report.

```shell
$ make coverage
```

The code coverage report is saved in `build/external/Build/server/coverage/index.html`.

## Wishlist

- Include observability (prometheus for example)
- Tracing

[drogon]: https://github.com/an-tao/drogon
[spdlog]: https://github.com/gabime/spdlog
