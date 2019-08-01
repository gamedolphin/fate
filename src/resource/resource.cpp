#include "fate/resource.h"
#include "fate/log.h"
#include <bgfx/bgfx.h>
#include <bimg/decode.h>
#include <bx/allocator.h>
#include <fstream>
#include <entt/entt.hpp>

namespace Fate {

  bx::DefaultAllocator s_allocator;

  static void imageReleaseCb(void* _ptr, void* _userData)
  {
    BX_UNUSED(_ptr);
    bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
    bimg::imageFree(imageContainer);
  }

  bgfx::TextureHandle loadTexture(std::string fileName) {
    std::ifstream ifs(fileName);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()) );

    if(!ifs.is_open()) {
      LogMessage("Could not open texture. Probably crashing");
    }

    bimg::ImageContainer* imageContainer = bimg::imageParse(&s_allocator, (void*)content.c_str(), (uint32_t)content.length());

    const bgfx::Memory* mem = bgfx::makeRef(
                      imageContainer->m_data
                    , imageContainer->m_size
                    , imageReleaseCb
                    , imageContainer
                    );

    return bgfx::createTexture2D(
                      uint16_t(imageContainer->m_width)
                    , uint16_t(imageContainer->m_height)
                    , 1 < imageContainer->m_numMips
                    , imageContainer->m_numLayers
                    , bgfx::TextureFormat::Enum(imageContainer->m_format)
                    , 0
                    , mem
                    );
  };

  void ResourceManager::LoadTexture(std::string fileName, std::string name) {
    auto textureHandle = loadTexture(fileName);
    auto key = entt::hashed_string{name.c_str()};

    textures.insert(std::make_pair(key,std::make_shared<bgfx::TextureHandle>(textureHandle)));
  }
}
