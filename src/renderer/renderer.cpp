#include "fate/renderer.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bimg/decode.h>
#include <bx/allocator.h>
#include <bx/math.h>
#include <cmath>
#include <entt/entt.hpp>
#include <fstream>
#include <thread>  // std::thread
#include "fate/component_camera.h"
#include "fate/component_render.h"
#include "fate/component_transform.h"
#include "fate/core.h"
#include "fate/entity.h"
#include "fate/gamestate.h"
#include "fate/log.h"
#include "fate/sprite.h"

namespace Fate {

using namespace std::chrono_literals;
typedef std::chrono::duration<float, std::milli> fsec;

void SetScale(float *mtx, Vector3 scale) {
  mtx[0] = scale.x;
  mtx[5] = scale.y;
  mtx[10] = scale.y;
};

void SetMatrix(float *mtx, Vector3 position, Vector3 rotation, Vector3 scale) {
  bx::mtxRotateXYZ(mtx, rotation.x, rotation.y, rotation.z);
  mtx[0] = scale.x;
  mtx[5] = scale.y;
  mtx[10] = scale.z;
  mtx[12] = position.x;
  mtx[13] = position.y;
  mtx[14] = position.z;
}

void SetMatrix(float *mtx, const Transform &transform) {
  if (transform.isDirty == false) {
    return;
  }
  auto &rotation = transform.rotation;
  auto &position = transform.position;
  auto &scale = transform.scale;
  bx::mtxRotateXYZ(mtx, rotation.x, rotation.y, rotation.z);
  SetScale(mtx, scale);
  mtx[12] = position.x;
  mtx[13] = position.y;
  mtx[14] = position.z;
};

void CreateDefaultCamera(WindowState &windowState, entt::registry &registry) {
  auto camera = registry.create();
  auto &transform = registry.assign<Transform>(camera);
  transform.position = {0, 0, 5};
  transform.rotation = {0, 0, 0};
  auto &component = registry.assign<CameraComponent>(camera);
  component = {
      .viewId = 0,
      .fov = 60.0f,
      .aspectRatio = float(windowState.width) / float(windowState.height),
      .near = 1.0f,
      .far = 100.0f,
      .viewPort = {0, 0, 1, 1},
      .orthoSize = (float)windowState.height / 2};
}

void SetupCamera(CameraComponent &cameraInfo, WindowState &windowState) {
  if (cameraInfo.dirty) {
    if (cameraInfo.cameraType == CameraType::ORTHOGRAPHIC) {
      bx::mtxOrtho(cameraInfo.projectionMatrix,
                   -cameraInfo.orthoSize * cameraInfo.aspectRatio,
                   cameraInfo.orthoSize * cameraInfo.aspectRatio,
                   -cameraInfo.orthoSize, cameraInfo.orthoSize, cameraInfo.near,
                   cameraInfo.far, 0, bgfx::getCaps()->homogeneousDepth);
    } else {
      bx::mtxProj(cameraInfo.projectionMatrix, cameraInfo.fov,
                  cameraInfo.aspectRatio, cameraInfo.near, cameraInfo.far,
                  bgfx::getCaps()->homogeneousDepth);
    }
    cameraInfo.dirty = false;
  }
}

entt::entity &Renderer::MakeSprite(entt::entity &entity, GameState &state,
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

  // automatically create a transform matrix whenever a transform is created
  entt::connect<Transform, TransformMatrix>(
      entityState.registry.on_construct<Transform>());

  bgfx::PlatformData pd;
  pd.ndt = GetDisplayType(windowState);
  pd.nwh = GetWindowHandle(windowState);

  bgfx::Init init;
  init.vendorId = BGFX_PCI_ID_NONE;
  init.deviceId = 0;
  init.platformData = pd;
  init.resolution.width = windowState.width;
  init.resolution.height = windowState.height;

  bgfx::renderFrame();
  bgfx::init(init);

  LoadShaderProgram(renderState.shaderState, "shaders/sprite.vshader.bin",
                    "shaders/sprite.fshader.bin", "sprite");

  InitializeSpriteRenderProperties(renderState.shaderState,
                                   renderState.spriteConstants);

  bgfx::reset(windowState.width, windowState.height, BGFX_RESET_VSYNC);
  // Enable debug text.
  bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

  auto cameras = entityState.registry.view<Transform, CameraComponent>();
  if (cameras.size() == 0) {
    CreateDefaultCamera(windowState, entityState.registry);
  }

  for (auto &camera : cameras) {
    auto &cameraInfo = cameras.get<CameraComponent>(camera);
    auto &viewPort = cameraInfo.viewPort;
    bgfx::setViewRect(cameraInfo.viewId, viewPort.x, viewPort.y,
                      uint16_t(viewPort.width * windowState.width),
                      uint16_t(viewPort.height * windowState.height));

    // Clear the view rect
    bgfx::setViewClear(cameraInfo.viewId, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                       0x443355FF, 1.0f, 0);

    bgfx::touch(cameraInfo.viewId);
  }

  renderState.rendererInitialized = true;
}

void Renderer::UpdateTransforms(GameState &gameState) {
  auto &registry = gameState.entityState.registry;
  registry.view<TransformMatrix, Transform>().each(
      [](TransformMatrix &transformMatrix, Transform &transform) {
        SetMatrix(transformMatrix.mtx, transform);
        transform.isDirty = false;
      });

  // sprite transforms
  registry.view<TransformMatrix, const Transform, const Sprite>().each(
      [](TransformMatrix &transformMatrix, const Transform &transform,
         const Sprite &sprite) {
        auto scale =
            Vector3{transform.scale.x * sprite.texture.size.width,
                    transform.scale.y * sprite.texture.size.height, 1.0f};

        // scale according to sprite dimensions
        SetScale(transformMatrix.mtx, scale);
      });
}

void Renderer::SetupCameras(GameState &gameState) {
  auto &windowState = gameState.windowState;
  gameState.entityState.registry.view<CameraComponent>().each(
      [&windowState](CameraComponent &cameraComponent) {
        SetupCamera(cameraComponent, windowState);
      });
}

void ShutdownBGFX(RenderState &renderState) {
  DestroySpriteRenderProperties(renderState.spriteConstants);
  bgfx::shutdown();
}

void Renderer::StartRenderer(GameState &gameState) {
  auto renderLoop = [&gameState]() {
    using clock = std::chrono::high_resolution_clock;
    auto timestep = std::chrono::nanoseconds(16ms);
    auto startTime = clock::now();
    auto frameTimeStart = clock::now();
    std::chrono::nanoseconds lag = std::chrono::nanoseconds(0ns);
    Renderer::InitializeRenderer(gameState.windowState, gameState.renderState,
                                 gameState.entityState);

    while (gameState.isRunning) {
      auto frameTime = clock::now();
      auto deltaTime = frameTime - frameTimeStart;
      frameTimeStart = frameTime;
      lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);

      while (lag >= timestep) {
        lag -= timestep;
        // busy wait
      }
      Renderer::UpdateTransforms(gameState);
      Renderer::SetupCameras(gameState);
      Renderer::Render(gameState);
    }
    ShutdownBGFX(gameState.renderState);
  };

  gameState.renderState.renderThread = std::thread(renderLoop);

  while (gameState.renderState.rendererInitialized == false) {
    std::this_thread::yield();
  }
}

void Renderer::Render(GameState &gameState) {
  WindowState &windowState = gameState.windowState;
  RenderState &renderState = gameState.renderState;
  EntityState &entityState = gameState.entityState;

  entityState.registry.view<const TransformMatrix, const CameraComponent>()
      .each([&windowState, &entityState, &renderState](
                const TransformMatrix &cameraTransform,
                const CameraComponent &cameraInfo) {
        bgfx::setViewTransform(cameraInfo.viewId, cameraTransform.mtx,
                               cameraInfo.projectionMatrix);

        auto &cameraRect = cameraInfo.viewPort;
        bgfx::setViewRect(cameraInfo.viewId, cameraRect.x, cameraRect.y,
                          cameraRect.width * windowState.width,
                          cameraRect.height * windowState.height);

        bgfx::touch(cameraInfo.viewId);

        {  // render sprites

          entityState.registry.view<const TransformMatrix, const Sprite>().each(
              [&renderState, &cameraInfo](const TransformMatrix &transform,
                                          const Sprite &sprite) {
                bgfx::setTransform(transform.mtx);

                bgfx::setVertexBuffer(
                    cameraInfo.viewId,
                    *renderState.spriteConstants.vertexBufferHandle);
                bgfx::setIndexBuffer(
                    *renderState.spriteConstants.indexBufferHandle);
                bgfx::setTexture(0, *renderState.spriteConstants.textureUniform,
                                 *sprite.texture.textureHandle);
                bgfx::setState(BGFX_STATE_DEFAULT);
                bgfx::submit(cameraInfo.viewId,
                             *renderState.spriteConstants.programHandle);
              });
        }
        bgfx::frame();
      });
}

void Renderer::ShutdownRenderer(GameState &gameState) {
  LogMessage("Shutting down renderer");
  gameState.renderState.renderThread.join();
}
};  // namespace Fate
