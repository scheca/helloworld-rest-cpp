#include "controller.h"
#include "error.h"
#include "log/log.h"

using namespace std;
using namespace drogon;
using namespace service;
using namespace logging;

namespace api {
namespace v1 {

HelloWorld::HelloWorld(Service &s) : service_(s) {}

void HelloWorld::status(const drogon::HttpRequestPtr &req,
                        function<void(const drogon::HttpResponsePtr &)> &&callback) const {
    auto resp(HttpResponse::newHttpResponse());

    auto err(service_.status());
    auto code(mapError(err));

    resp->setStatusCode(code);
    return callback(resp);
}

void HelloWorld::greet(const drogon::HttpRequestPtr &req,
                       function<void(const drogon::HttpResponsePtr &)> &&callback) const {
    auto resp(HttpResponse::newHttpResponse());

    auto json(req->getJsonObject());
    if (json == nullptr) {
        logger.error("Expected well-formatted JSON: {}", req->getJsonError());
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        return callback(resp);
    }

    auto greeting((*json)["greeting"]);
    if (!greeting.isString()) {
        logger.error("Expected greeting string, got type: {}", greeting.type());
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        return callback(resp);
    }

    auto greetingStr(greeting.asString());
    auto [helloResp, err](service_.greet(HelloRequest{.greeting = greetingStr}));
    auto code(mapError(err));

    if (code == HttpStatusCode::k200OK) {
        Json::Value ret;
        ret["response"] = helloResp.response;
        resp = HttpResponse::newHttpJsonResponse(ret);
    }

    resp->setStatusCode(code);
    return callback(resp);
}

}  // namespace v1
}  // namespace api