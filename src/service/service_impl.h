#pragma once

#include "service.h"

namespace service {

class ServiceImpl : public Service {
  public:
    ServiceImpl();

  private:
    Error status() const override;
    std::tuple<HelloResponse, Error> greet(const HelloRequest&) override;
};

}  // namespace service