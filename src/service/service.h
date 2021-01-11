#pragma once

#include <string>
#include <tuple>

#include "error.h"

namespace service {

struct HelloRequest {
    std::string greeting;
};

struct HelloResponse {
    std::string response;
};

class Service {
  public:
    virtual Error status() const = 0;
    virtual std::tuple<HelloResponse, Error> greet(const HelloRequest&) = 0;
};

}  // namespace service
