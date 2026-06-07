#include "../include/yds_opengl_sdl_context.h"
#include "../include/yds_sdl_window.h"
#include "../include/yds_opengl_device.h"

ysOpenGLSdlContext::ysOpenGLSdlContext() : ysOpenGLVirtualContext(ysWindowSystemObject::Platform::SDL) {
    m_glContext = nullptr;
    m_device = nullptr;
}

ysOpenGLSdlContext::~ysOpenGLSdlContext() {
}

ysError ysOpenGLSdlContext::CreateRenderingContext(ysOpenGLDevice *device, ysWindow *window, int major, int minor) {
    YDS_ERROR_DECLARE("CreateRenderingContext");

    if (window->GetPlatform() != ysWindowSystemObject::Platform::SDL) {
        return YDS_ERROR_RETURN(ysError::IncompatiblePlatforms);
    }

    ysSdlWindow *sdlWindow = static_cast<ysSdlWindow *>(window);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_glContext = SDL_GL_CreateContext(sdlWindow->GetSDLWindow());
    if (!m_glContext) {
        return YDS_ERROR_RETURN(ysError::CouldNotCreateContext);
    }

    m_device = device;
    m_targetWindow = window;
    
    m_isRealContext = true;
    device->UpdateContext();

    LoadAllExtensions();

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysOpenGLSdlContext::DestroyContext() {
    if (m_glContext) {
        SDL_GL_DestroyContext(m_glContext);
        m_glContext = nullptr;
    }
    return ysError::None;
}

ysError ysOpenGLSdlContext::TransferContext(ysOpenGLVirtualContext *context) {
    return ysError::None;
}

ysError ysOpenGLSdlContext::SetContextMode(ContextMode mode) {
    return ysError::None;
}

ysError ysOpenGLSdlContext::SetContext(ysRenderingContext *realContext) {
    if (realContext) {
        ysOpenGLSdlContext *sdlCtx = static_cast<ysOpenGLSdlContext *>(realContext);
        ysSdlWindow *sdlWindow = static_cast<ysSdlWindow *>(m_targetWindow);
        SDL_GL_MakeCurrent(sdlWindow->GetSDLWindow(), sdlCtx->m_glContext);
    } else {
        SDL_GL_MakeCurrent(nullptr, nullptr);
    }
    return ysError::None;
}

ysError ysOpenGLSdlContext::Present() {
    ysSdlWindow *sdlWindow = static_cast<ysSdlWindow *>(m_targetWindow);
    SDL_GL_SwapWindow(sdlWindow->GetSDLWindow());
    return ysError::None;
}

void ysOpenGLSdlContext::LoadAllExtensions() {
    // Manually load extensions using SDL_GL_GetProcAddress 
    // This is required for OpenGL to work properly
#define LOAD_GL(name, type) name = (type)SDL_GL_GetProcAddress(#name)

    LOAD_GL(glGenBuffers, PFNGLGENBUFFERSPROC);
    LOAD_GL(glDeleteBuffers, PFNGLDELETEBUFFERSPROC);
    LOAD_GL(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC);
    LOAD_GL(glBindBuffer, PFNGLBINDBUFFERPROC);
    LOAD_GL(glBindBufferRange, PFNGLBINDBUFFERRANGEPROC);
    LOAD_GL(glBufferData, PFNGLBUFFERDATAPROC);
    LOAD_GL(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC);
    LOAD_GL(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC);
    LOAD_GL(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC);
    LOAD_GL(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC);
    LOAD_GL(glVertexAttribIPointer, PFNGLVERTEXATTRIBIPOINTERPROC);
    LOAD_GL(glVertexAttrib3f, PFNGLVERTEXATTRIB3FPROC);
    LOAD_GL(glVertexAttrib4f, PFNGLVERTEXATTRIB4FPROC);
    LOAD_GL(glDeleteProgram, PFNGLDELETEPROGRAMPROC);
    LOAD_GL(glDeleteShader, PFNGLDELETESHADERPROC);
    LOAD_GL(glCreateShader, PFNGLCREATESHADERPROC);
    LOAD_GL(glShaderSource, PFNGLSHADERSOURCEPROC);
    LOAD_GL(glCompileShader, PFNGLCOMPILESHADERPROC);
    LOAD_GL(glCreateProgram, PFNGLCREATEPROGRAMPROC);
    LOAD_GL(glAttachShader, PFNGLATTACHSHADERPROC);
    LOAD_GL(glDetachShader, PFNGLDETACHSHADERPROC);
    LOAD_GL(glLinkProgram, PFNGLLINKPROGRAMPROC);
    LOAD_GL(glUseProgram, PFNGLUSEPROGRAMPROC);
    LOAD_GL(glBindAttribLocation, PFNGLBINDATTRIBLOCATIONPROC);
    LOAD_GL(glBindFragDataLocation, PFNGLBINDFRAGDATALOCATIONPROC);
    LOAD_GL(glGetFragDataLocation, PFNGLGETFRAGDATALOCATIONPROC);
    LOAD_GL(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC);
    LOAD_GL(glGetShaderiv, PFNGLGETSHADERIVPROC);
    LOAD_GL(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC);
    LOAD_GL(glDrawBuffers, PFNGLDRAWBUFFERSPROC);
    LOAD_GL(glUniform4f, PFNGLUNIFORM4FPROC);
    LOAD_GL(glUniform4fv, PFNGLUNIFORM4FVPROC);
    LOAD_GL(glUniform3fv, PFNGLUNIFORM3FVPROC);
    LOAD_GL(glUniform2fv, PFNGLUNIFORM2FVPROC);
    LOAD_GL(glUniform3f, PFNGLUNIFORM3FPROC);
    LOAD_GL(glUniform2f, PFNGLUNIFORM2FPROC);
    LOAD_GL(glUniform1f, PFNGLUNIFORM1FPROC);
    LOAD_GL(glUniform1i, PFNGLUNIFORM1IPROC);
    LOAD_GL(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC);
    LOAD_GL(glUniformMatrix3fv, PFNGLUNIFORMMATRIX3FVPROC);
    LOAD_GL(glGetProgramiv, PFNGLGETPROGRAMIVPROC);
    LOAD_GL(glGetActiveUniformName, PFNGLGETACTIVEUNIFORMNAMEPROC);
    LOAD_GL(glGetActiveUniformsiv, PFNGLGETACTIVEUNIFORMSIVPROC);
    LOAD_GL(glGetActiveUniform, PFNGLGETACTIVEUNIFORMPROC);
    LOAD_GL(glDrawElementsBaseVertex, PFNGLDRAWELEMENTSBASEVERTEXPROC);
    LOAD_GL(glTexImage2DMultisample, PFNGLTEXIMAGE2DMULTISAMPLEPROC);
    LOAD_GL(glActiveTexture, PFNGLACTIVETEXTUREPROC);
    LOAD_GL(glGenerateMipmap, PFNGLGENERATEMIPMAPPROC);
    LOAD_GL(glMapBuffer, PFNGLMAPBUFFERPROC);
    LOAD_GL(glMapBufferRange, PFNGLMAPBUFFERRANGEPROC);
    LOAD_GL(glUnmapBuffer, PFNGLUNMAPBUFFERPROC);
    LOAD_GL(glGenRenderbuffers, PFNGLGENRENDERBUFFERSPROC);
    LOAD_GL(glDeleteRenderbuffers, PFNGLDELETERENDERBUFFERSPROC);
    LOAD_GL(glBindRenderbuffer, PFNGLBINDRENDERBUFFERPROC);
    LOAD_GL(glRenderbufferStorage, PFNGLRENDERBUFFERSTORAGEPROC);
    LOAD_GL(glRenderbufferStorageMultisample, PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC);
    LOAD_GL(glCopyBufferSubData, PFNGLCOPYBUFFERSUBDATAPROC);
    LOAD_GL(glBufferSubData, PFNGLBUFFERSUBDATAPROC);
    LOAD_GL(glGenFramebuffers, PFNGLGENFRAMEBUFFERSPROC);
    LOAD_GL(glDeleteFramebuffers, PFNGLDELETEFRAMEBUFFERSPROC);
    LOAD_GL(glBindFramebuffer, PFNGLBINDFRAMEBUFFERPROC);
    LOAD_GL(glFramebufferTexture2D, PFNGLFRAMEBUFFERTEXTURE2DPROC);
    LOAD_GL(glFramebufferRenderbuffer, PFNGLFRAMEBUFFERRENDERBUFFERPROC);
    LOAD_GL(glCheckFramebufferStatus, PFNGLCHECKFRAMEBUFFERSTATUSPROC);
    LOAD_GL(glBlitFramebuffer, PFNGLBLITFRAMEBUFFERPROC);
    LOAD_GL(glBlendEquation, PFNGLBLENDEQUATIONPROC);
}
