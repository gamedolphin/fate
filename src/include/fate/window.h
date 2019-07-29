#pragma once

struct SDL_Window;

namespace Fate {

  struct WindowState {
    SDL_Window* windowHandle;
  };

  class WindowManager {
  public:
    void CreateWindow(WindowState& state);
    void ShutdownWindow(WindowState& state);
    ~WindowManager();
  };

  void* GetDisplayType(WindowState& windowState);
  void* GetWindowHandle(WindowState& windowState);
}
