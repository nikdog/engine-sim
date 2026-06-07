#ifndef OPENGL_H
#define OPENGL_H

#ifdef _MSC_VER
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#else
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_opengl_glext.h>
#endif

#endif /* OPENGL_H */
