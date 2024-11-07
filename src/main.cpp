#include <chrono>
#include <thread>
#include <string>
#include "SafeGuard/SafeGuard.h"
#include "Common/Logger.h"
int main(int argc, char* argv[])
{
    if(argc != 2) {
        Common::logWarn("Usage:{} <config_path>", argv[0]);
        return -1;
    }
    std::string config_path = argv[1];
    SafeGuard::SafeGuard guard;
    if(guard.Initialize(config_path)) {
        guard.MainLoop();
    }

    return 0;
}