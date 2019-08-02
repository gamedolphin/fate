#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <entt/entt.hpp>

namespace bgfx {
  struct ProgramHandle;
}

namespace Fate {

  class ShaderManager {
  public:
    std::unordered_map<entt::hashed_string::hash_type,std::shared_ptr<bgfx::ProgramHandle>> programs = {};
    void LoadProgram(const std::string &vertexPath, const std::string &fragmentPath, std::string key);
  };
}
