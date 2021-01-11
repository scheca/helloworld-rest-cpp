#include <unordered_map>

#include "error.h"

using namespace std;
using namespace drogon;
using namespace service;

namespace {

const unordered_map<Error, HttpStatusCode> errorMap = {
    {Error::Ok, HttpStatusCode::k200OK},
};

}

namespace api {
namespace v1 {

HttpStatusCode mapError(const service::Error err) {
    auto cit(errorMap.find(err));
    if (cit != errorMap.cend()) {
        return cit->second;
    }
    return HttpStatusCode::k500InternalServerError;
}

}  // namespace v1
}  // namespace api