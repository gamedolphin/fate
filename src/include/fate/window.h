#pragma once
#include <string>

struct SDL_Window;

namespace Fate {

  struct WindowState {
    SDL_Window* windowHandle;
    int width, height;
    std::string windowTitle;
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
