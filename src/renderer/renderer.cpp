#include "fate/renderer.h"
#include "fate/core.h"
#include "fate/gamestate.h"
#include "fate/log.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

namespace Fate {

  void Renderer::InitializeRenderer(WindowState &windowState, RenderState &renderState) {
    LogMessage("Initializing renderer...");

    bgfx::PlatformData pd;
    pd.ndt = GetDisplayType(windowState);
    pd.nwh = GetWindowHandle(windowState);

    bgfx::Init init;
    init.vendorId = BGFX_PCI_ID_NONE;
    init.deviceId = 0;
    init.platformData = pd;
    init.resolution.width  = 300;
    init.resolution.height = 200;

    bgfx::renderFrame();
    bgfx::init(init);
  }

  Renderer::~Renderer() {
    LogMessage("Shutting down renderer");
    bgfx::shutdown();
  }
};
