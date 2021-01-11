#pragma once

#include <drogon/HttpController.h>

#include "service/service.h"

namespace api {
namespace v1 {

class HelloWorld : public drogon::HttpController<HelloWorld, false> {
  public:
    explicit HelloWorld(service::Service &);

  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HelloWorld::status, "/status", drogon::Get);
    ADD_METHOD_TO(HelloWorld::greet, "/greet", drogon::Post);
    METHOD_LIST_END

    void status(const drogon::HttpRequestPtr &req,
                std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;
    void greet(const drogon::HttpRequestPtr &req,
               std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;

  private:
    service::Service &service_;
};

}  // namespace v1
}  // namespace api