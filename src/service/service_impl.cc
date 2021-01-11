#include "service_impl.h"
#include "log/log.h"

using namespace std;
using namespace logging;

namespace service {

ServiceImpl::ServiceImpl() {}

Error ServiceImpl::status() const {
    logger.debug("Requesting status");
    return Error::Ok;
}

tuple<HelloResponse, Error> ServiceImpl::greet(const HelloRequest& req) {
    logger.debug("Requesting greet");
    return {HelloResponse{.response = "Hi there!, you told me: " + req.greeting}, Error::Ok};
}

}  // namespace service