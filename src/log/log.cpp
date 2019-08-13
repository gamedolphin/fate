#include "fate/log.h"
#include "spdlog/spdlog.h"

namespace Fate {

void LogMessage(const std::string& msg) { spdlog::info(msg); }

void LogError(const std::string& msg) { spdlog::error(msg); }

};  // namespace Fate
