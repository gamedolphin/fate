#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <entt/entt.hpp>

namespace bgfx {
  struct ProgramHandle;
}

namespace Fate {

  struct ShaderState {
    std::unordered_map<entt::hashed_string::hash_type,std::shared_ptr<bgfx::ProgramHandle>> programs = {};
  };

  void LoadShaderProgram(ShaderState &state, const std::string &vertexPath, const std::string &fragmentPath, std::string key);
}
