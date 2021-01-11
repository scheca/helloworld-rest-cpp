#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "api/v1/controller.h"
#include "service/mock/service.h"

using namespace std;
using namespace std::placeholders;
using namespace ::testing;
using namespace api::v1;
using namespace service;

namespace {

class MockCallbacks {
  public:
    MOCK_METHOD(void, status, (const drogon::HttpResponsePtr&), (const));
    MOCK_METHOD(void, greet, (const drogon::HttpResponsePtr&), (const));
};

class ControllerTest : public Test {
  protected:
    ControllerTest() : controller_(mockService_) {}

  protected:
    MockCallbacks mockCb_;
    service::mock::MockService mockService_;
    HelloWorld controller_;
};

TEST_F(ControllerTest, Status) {
    EXPECT_CALL(mockService_, status()).WillOnce(Return(Error::Ok));
    EXPECT_CALL(mockCb_, status(_)).WillOnce([](const drogon::HttpResponsePtr& resp) {
        EXPECT_EQ(drogon::HttpStatusCode::k200OK, resp->statusCode());
    });

    auto req(drogon::HttpRequest::newHttpRequest());
    controller_.status(req, bind(&MockCallbacks::status, &mockCb_, _1));
}

TEST_F(ControllerTest, Greet_Ok) {
    EXPECT_CALL(mockService_, greet(_))
        .WillOnce(
            DoAll([](const HelloRequest& req) { EXPECT_EQ("hi there!", req.greeting); },
                  Return(make_tuple(HelloResponse{.response = "greeting response"}, Error::Ok))));

    EXPECT_CALL(mockCb_, greet(_)).WillOnce([](const drogon::HttpResponsePtr& resp) {
        EXPECT_EQ(drogon::HttpStatusCode::k200OK, resp->statusCode());
        auto jsonBody(resp->getJsonObject());
        EXPECT_THAT(jsonBody, NotNull());
        auto response((*jsonBody)["response"]);
        EXPECT_TRUE(response.isString());
        EXPECT_EQ("greeting response", response.asString());
    });

    auto jsonBody(Json::Value{});
    jsonBody["greeting"] = "hi there!";
    auto req(drogon::HttpRequest::newHttpJsonRequest(jsonBody));
    controller_.greet(req, bind(&MockCallbacks::greet, &mockCb_, _1));
}

TEST_F(ControllerTest, Greet_BadRequest) {
    EXPECT_CALL(mockCb_, greet(_)).WillOnce([](const drogon::HttpResponsePtr& resp) {
        EXPECT_EQ(drogon::HttpStatusCode::k400BadRequest, resp->statusCode());
    });

    auto jsonBody(Json::Value{});
    jsonBody["greeting"] = 123;
    auto req(drogon::HttpRequest::newHttpJsonRequest(jsonBody));
    controller_.greet(req, bind(&MockCallbacks::greet, &mockCb_, _1));
}

TEST_F(ControllerTest, Greet_InvalidJson) {
    EXPECT_CALL(mockCb_, greet(_)).WillOnce([](const drogon::HttpResponsePtr& resp) {
        EXPECT_EQ(drogon::HttpStatusCode::k400BadRequest, resp->statusCode());
    });

    auto req(drogon::HttpRequest::newHttpRequest());
    controller_.greet(req, bind(&MockCallbacks::greet, &mockCb_, _1));
}

}  // namespace