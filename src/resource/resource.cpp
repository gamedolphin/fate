#include "fate/resource.h"
#include <bgfx/bgfx.h>
#include <bimg/decode.h>
#include <bx/allocator.h>
#include <entt/entt.hpp>
#include <fstream>
#include "fate/gamestate.h"
#include "fate/log.h"

namespace Fate {

bx::DefaultAllocator s_allocator;

static void imageReleaseCb(void* _ptr, void* _userData) {
  BX_UNUSED(_ptr);
  bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
  bimg::imageFree(imageContainer);
}

TextureResource loadTexture(std::string fileName) {
  std::ifstream ifs(fileName);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));

  if (!ifs.is_open()) {
    LogMessage("Could not open texture. Probably crashing");
  }

  bimg::ImageContainer* imageContainer = bimg::imageParse(
      &s_allocator, (void*)content.c_str(), (uint32_t)content.length());

  const bgfx::Memory* mem =
      bgfx::makeRef(imageContainer->m_data, imageContainer->m_size,
                    imageReleaseCb, imageContainer);

  auto textureHandle = bgfx::createTexture2D(
      uint16_t(imageContainer->m_width), uint16_t(imageContainer->m_height),
      1 < imageContainer->m_numMips, imageContainer->m_numLayers,
      bgfx::TextureFormat::Enum(imageContainer->m_format), 0, mem);

  TextureResource resource = {
      .textureHandle = std::make_shared<bgfx::TextureHandle>(textureHandle),
      .size = RenderSize{.height = imageContainer->m_height,
                         .width = imageContainer->m_width}};
  return resource;
};  // namespace Fate

void Resources::LoadTexture(ResourceState& state, std::string fileName,
                            std::string name) {
  auto textureHandle = loadTexture(fileName);
  auto key = entt::hashed_string{name.c_str()};
  state.textures.insert(std::make_pair(key, textureHandle));
}

void Resources::LoadTexture(GameState& state, std::string fileName,
                            std::string name) {
  auto textureHandle = loadTexture(fileName);
  auto key = entt::hashed_string{name.c_str()};

  state.resourceState.textures.insert(std::make_pair(key, textureHandle));
}

RenderSize Resources::GetTextureSize(GameState& state,
                                     std::string textureName) {
  auto key = entt::hashed_string{textureName.c_str()};
  auto resource = state.resourceState.textures.at(key);
  return resource.size;
}

void Resources::UnloadAllResources(GameState& state) {
  // destroy all textures
  for (auto texture : state.resourceState.textures) {
    bgfx::destroy(*texture.second.textureHandle);
  }
}
}  // namespace Fate
