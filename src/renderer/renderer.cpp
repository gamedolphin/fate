#include "fate/renderer.h"
#include "fate/core.h"
#include "fate/gamestate.h"
#include "fate/log.h"
#include "fate/entity.h"
#include "fate/component_render.h"
#include "fate/component_transform.h"
#include "fate/component_camera.h"
#include "fate/sprite.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <bx/allocator.h>
#include <bimg/decode.h>
#include <entt/entt.hpp>
#include <cmath>
#include <fstream>

namespace Fate {

  void SetMatrix(Transform &transform, float mtx[16]) {
    auto rotation = transform.rotation;
    bx::mtxRotateXYZ(mtx, rotation.x, rotation.y, rotation.z);
    mtx[12] = transform.position.x;
    mtx[13] = transform.position.y;
    mtx[14] = transform.position.z;
  };

  void CreateDefaultCamera(WindowState& windowState, entt::registry &registry) {
    auto camera = registry.create();
    auto &transform = registry.assign<Transform>(camera);
    transform.position = { 0, 0, 1 };
    transform.rotation = { 0, M_PI, 0 };
    auto &component = registry.assign<CameraComponent>(camera);
    component = {
                 0,
                 60.0f,
                 float(windowState.width)/float(windowState.height),
                 0.1f,
                 100.0f
    };
    component.viewPort = { 0, 0, 1, 1 };
  }

  entt::entity& Renderer::MakeSprite(entt::entity &entity,
                           GameState& state,
                           std::string textureName) {
    auto &transform = state.entityState.registry.assign<Transform>(entity);
    auto &render = state.entityState.registry.assign<Sprite>(entity);

    auto textureId = entt::hashed_string{textureName.c_str()};
    render.texture = state.resourceState.textures.at(textureId);

    return entity;
  }

  void Renderer::InitializeRenderer(WindowState &windowState,
                                    RenderState &renderState,
                                    EntityState &entityState) {
    LogMessage("Initializing renderer...");

    bgfx::PlatformData pd;
    pd.ndt = GetDisplayType(windowState);
    pd.nwh = GetWindowHandle(windowState);

    bgfx::Init init;
    init.vendorId = BGFX_PCI_ID_NONE;
    init.deviceId = 0;
    init.platformData = pd;
    init.resolution.width  = windowState.width;
    init.resolution.height = windowState.height;

    bgfx::renderFrame();
    bgfx::init(init);

    LoadShaderProgram(renderState.shaderState,"shaders/cubes.vshader.bin", "shaders/cubes.fshader.bin", "cubes");
    LoadShaderProgram(renderState.shaderState,"shaders/sprite.vshader.bin", "shaders/sprite.fshader.bin", "sprite");

    InitializeSpriteRenderProperties(renderState.shaderState,
                                     renderState.spriteConstants);

    bgfx::reset(windowState.width, windowState.height, BGFX_RESET_VSYNC);
     // Enable debug text.
    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    auto cameras = entityState.registry.view<Transform,CameraComponent>();
    if(cameras.size() == 0) {
      CreateDefaultCamera(windowState, entityState.registry);
    }

    for(auto &camera : cameras) {
      auto &cameraInfo = cameras.get<CameraComponent>(camera);
      auto &viewPort = cameraInfo.viewPort;
      bgfx::setViewRect(cameraInfo.viewId,
                        viewPort.x,
                        viewPort.y,
                        uint16_t(viewPort.width * windowState.width),
                        uint16_t(viewPort.height * windowState.height));

      // Clear the view rect
      bgfx::setViewClear(cameraInfo.viewId,
                         BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                         0x443355FF, 1.0f, 0);

      bgfx::touch(cameraInfo.viewId);
    }
  }

  void Renderer::Render(WindowState& windowState,
                        RenderState &renderState,
                        EntityState &entityState) {

    auto cameras = entityState.registry.view<Transform, CameraComponent>();
    for(auto cameraEntity: cameras) {
        auto &cameraTransform = cameras.get<Transform>(cameraEntity);
        auto &cameraPosition = cameraTransform.position;
        auto &cameraRotation = cameraTransform.rotation;

        float view[16];
        SetMatrix(cameraTransform, view);
        auto &cameraInfo = cameras.get<CameraComponent>(cameraEntity);
        float proj[16];
        bx::mtxProj(proj,
                    cameraInfo.fov,
                    cameraInfo.aspectRatio,
                    cameraInfo.near,
                    cameraInfo.far,
                    bgfx::getCaps()->homogeneousDepth);

        bgfx::setViewTransform(cameraInfo.viewId, view, proj);

        auto &cameraRect = cameraInfo.viewPort;
        bgfx::setViewRect(cameraInfo.viewId,
                          cameraRect.x,
                          cameraRect.y,
                          cameraRect.width * windowState.width,
                          cameraRect.height * windowState.height);

        bgfx::touch(cameraInfo.viewId);

        { // render sprites

          auto renderables = entityState.registry.view<Transform,Sprite>();
          for(auto renderable : renderables) {
            auto &sprite = renderables.get<Sprite>(renderable);
            auto &transform = renderables.get<Transform>(renderable);

            float mtx[16];
            SetMatrix(transform, mtx);

            bgfx::setVertexBuffer(cameraInfo.viewId, *renderState.spriteConstants.vertexBufferHandle);
            bgfx::setIndexBuffer(*renderState.spriteConstants.indexBufferHandle);
            bgfx::setTexture(0, *renderState.spriteConstants.textureUniform,  *sprite.texture);
            bgfx::setState(BGFX_STATE_DEFAULT);
            bgfx::submit(cameraInfo.viewId, *renderState.spriteConstants.programHandle);
          }
        }
        bgfx::frame();
    }
  }

  void Renderer::ShutdownRenderer(WindowState &windowState, RenderState &renderState) {
    LogMessage("Shutting down renderer");
    DestroySpriteRenderProperties(renderState.spriteConstants);
    bgfx::shutdown();
  }
};
