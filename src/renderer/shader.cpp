#include "fate/shader.h"
#include "fate/log.h"
#include <bgfx/bgfx.h>
#include <unordered_map>
#include <memory>
#include <string>
#include <fstream>

namespace Fate {

  bgfx::ShaderHandle GetShader(const std::string &fileName) {
    std::ifstream ifs(fileName);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );

    if(!ifs.is_open()) {
      LogMessage("Could not load shader. Probably crashing");
    }

    const bgfx::Memory* mem = bgfx::copy(content.c_str(),content.length() + 1);
    mem->data[mem->size-1] = '\0';
    bgfx::ShaderHandle handle = bgfx::createShader(mem);
    return handle;
  }

  void LoadShaderProgram(ShaderState &state, const std::string &vertexPath, const std::string &fragmentPath, std::string key) {
    auto vertexHandle = GetShader(vertexPath);
    auto fragmentHandle = GetShader(fragmentPath);

    auto programHandle = bgfx::createProgram(vertexHandle, fragmentHandle, true);

    state.programs.insert(
        std::make_pair(entt::hashed_string{key.c_str()},
                       std::make_shared<bgfx::ProgramHandle>(programHandle)));
  }
}
