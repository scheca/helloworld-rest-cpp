#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "service/service_impl.h"

using namespace std;
using namespace ::testing;
using namespace service;

namespace {

class ServiceImplTest : public Test {
  protected:
    ServiceImplTest() : service_(serviceImpl_) {}

  private:
    void SetUp() override {
        // put here your test setup code
    }

    void TearDown() override {
        // put here your test teardown code
    }

  private:
    ServiceImpl serviceImpl_;

  protected:
    Service& service_;
};

TEST_F(ServiceImplTest, ResponseContainsRequest) {
    auto req(HelloRequest{.greeting = "hey man!"});
    auto [resp, err](service_.greet(req));

    EXPECT_EQ(err, Error::Ok);
    EXPECT_THAT(resp.response, HasSubstr("hey man!"));
}

}  // namespace