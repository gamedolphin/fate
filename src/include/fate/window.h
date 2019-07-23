#pragma once

typedef struct SDL_Window WindowHandle;

namespace Fate {

  struct WindowState {
  };

  class WindowManager {
  public:
    WindowHandle* window;
    void CreateWindow(WindowState& windowState);
    ~WindowManager();
  };
}
