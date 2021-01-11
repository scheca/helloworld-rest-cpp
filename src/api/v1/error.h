#pragma once

#include <drogon/HttpTypes.h>

#include "service/error.h"

namespace api {
namespace v1 {

drogon::HttpStatusCode mapError(const service::Error);

}
}  // namespace api