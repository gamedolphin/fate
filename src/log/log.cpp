#include "fate/log.h"
#include "spdlog/spdlog.h"

namespace Fate {

  void LogMessage(std::string msg) {
     spdlog::info(msg);
  }
};
