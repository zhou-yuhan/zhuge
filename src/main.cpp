#include <stdio.h>
#include <string>
#include <string_view>
#include "zhuge.hpp"
#include "easylogging++.hpp"
#include "config.hpp"
#include "time.hpp"
#include "task.hpp"

INITIALIZE_EASYLOGGINGPP

int main() {
    Config& config = Config::getInstance();
    LOG(INFO) << config["log"]["conf_file"];
    LOG(WARNING) << config["fortune_teller"]["window"];

    Time now = Time::Now();
    LOG(INFO) << now.Milliseconds() << " " << now.Microseconds();
    TaskManager task_manager;
    return 0;
}