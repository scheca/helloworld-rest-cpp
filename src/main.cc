#include <drogon/drogon.h>

#include "api/v1/controller.h"
#include "log/log.h"
#include "service/service_impl.h"

using namespace std;
using namespace drogon;
using namespace logging;

int main() {
    const auto port(8080);
    logger.info("Starting hello-world server on port {}", port);

    auto servis(service::ServiceImpl{});
    auto controller(make_shared<api::v1::HelloWorld>(servis));

    app()
        .setLogPath("./")
        .setLogLevel(trantor::Logger::kDebug)
        .addListener("0.0.0.0", port)
        .setThreadNum(16);

    app().registerController(controller);

    app().run();

    return 0;
}
