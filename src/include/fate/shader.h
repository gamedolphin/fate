#pragma once
#include <string>
#include <memory>
#include <unordered_map>

namespace Fate {

  class  Program;

  class ShaderManager {
    uint8_t keyVal = 0;
  public:
    std::unordered_map<uint8_t,std::shared_ptr<Program>> programs = {};
    uint8_t LoadProgram(const std::string &vertexPath, const std::string &fragmentPath);
  };
}
