#ifndef YDS_SDL_WINDOW_H
#define YDS_SDL_WINDOW_H

#include "yds_window.h"
#include <SDL3/SDL.h>

class ysSdlWindow : public ysWindow {
public:
    ysSdlWindow();
    virtual ~ysSdlWindow();

    virtual ysError InitializeWindow(ysWindow *parent, const char *title, WindowStyle style, int x, int y, int width, int height, ysMonitor *monitor) override;
    virtual ysError InitializeWindow(ysWindow *parent, const char *title, WindowStyle style, ysMonitor *monitor) override;

    SDL_Window* GetSDLWindow() const { return m_sdlWindow; }

    virtual bool SetWindowStyle(WindowStyle style) override;

protected:
    virtual void AL_SetSize(int width, int height) override;
    virtual void AL_SetLocation(int x, int y) override;

    SDL_Window* m_sdlWindow;
};

#endif
