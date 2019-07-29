#pragma once
#include <string>
#include <memory>

namespace bgfx {
  struct ShaderHandle;
  struct ProgramHandle;
}

namespace Fate {
  class Shader {
    std::unique_ptr<bgfx::ShaderHandle> vertexHandle;
    std::unique_ptr<bgfx::ShaderHandle> fragmentHandle;
  public:
    uint8_t ID;

    Shader();
    /* Shader &Use(); */
    void Compile(const std::string &vertexSource, const std::string *fragmentSource);
  };

  class Program {
    std::unique_ptr<bgfx::ProgramHandle> programHandle;
  };
}
