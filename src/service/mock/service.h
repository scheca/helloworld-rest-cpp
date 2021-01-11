#pragma once

#include <gmock/gmock.h>

#include "service/service.h"

namespace service {
namespace mock {

class MockService : public Service {
  public:
    MOCK_METHOD(Error, status, (), (const, override));
    MOCK_METHOD((std::tuple<HelloResponse, Error>), greet, (const HelloRequest&), (override));
};

}  // namespace mock
}  // namespace service