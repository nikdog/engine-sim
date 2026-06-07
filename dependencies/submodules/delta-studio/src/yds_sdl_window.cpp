#include "../include/yds_sdl_window.h"

ysSdlWindow::ysSdlWindow() : ysWindow(Platform::SDL) {
    m_sdlWindow = nullptr;
}

ysSdlWindow::~ysSdlWindow() {
    if (m_sdlWindow) {
        SDL_DestroyWindow(m_sdlWindow);
    }
}

ysError ysSdlWindow::InitializeWindow(ysWindow *parent, const char *title, WindowStyle style, int x, int y, int width, int height, ysMonitor *monitor) {
    YDS_ERROR_DECLARE("InitializeWindow");

    m_width = width;
    m_height = height;
    m_locationx = x;
    m_locationy = y;
    
    SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    if (style == WindowStyle::Fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    
    m_sdlWindow = SDL_CreateWindow(title, width, height, flags);
    if (!m_sdlWindow) {
        return YDS_ERROR_RETURN(ysError::CouldNotCreateGraphicsDevice);
    }
    
    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlWindow::InitializeWindow(ysWindow *parent, const char *title, WindowStyle style, ysMonitor *monitor) {
    return InitializeWindow(parent, title, style, 0, 0, 1024, 768, monitor);
}

void ysSdlWindow::AL_SetSize(int width, int height) {
    if (m_sdlWindow) SDL_SetWindowSize(m_sdlWindow, width, height);
}

void ysSdlWindow::AL_SetLocation(int x, int y) {
    if (m_sdlWindow) SDL_SetWindowPosition(m_sdlWindow, x, y);
}

bool ysSdlWindow::SetWindowStyle(WindowStyle style) {
    if (!m_sdlWindow) return false;

    ysWindow::SetWindowStyle(style);

    Uint32 flags = 0;
    switch (style) {
        case WindowStyle::Windowed:
            SDL_SetWindowFullscreen(m_sdlWindow, false);
            break;
        case WindowStyle::Fullscreen:
            SDL_SetWindowFullscreen(m_sdlWindow, true);
            break;
        case WindowStyle::Popup:
            SDL_SetWindowFullscreen(m_sdlWindow, false);
            break;
    }

    m_windowStyle = style;
    return true;
}
