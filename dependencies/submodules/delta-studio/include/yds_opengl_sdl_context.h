#ifndef YDS_OPENGL_SDL_CONTEXT_H
#define YDS_OPENGL_SDL_CONTEXT_H

#include "yds_opengl_context.h"
#include <SDL3/SDL.h>

class ysOpenGLDevice;

class ysOpenGLSdlContext : public ysOpenGLVirtualContext {
public:
    ysOpenGLSdlContext();
    virtual ~ysOpenGLSdlContext();

    ysError CreateRenderingContext(ysOpenGLDevice *device, ysWindow *window, int major, int minor);
    virtual ysError DestroyContext() override;
    virtual ysError TransferContext(ysOpenGLVirtualContext *context) override;
    virtual ysError SetContextMode(ContextMode mode) override;
    virtual ysError SetContext(ysRenderingContext *realContext) override;
    virtual ysError Present() override;

protected:
    void LoadAllExtensions();

    SDL_GLContext m_glContext;
    ysOpenGLDevice *m_device;
};

#endif
