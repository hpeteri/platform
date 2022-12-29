#ifndef N1_WINDOW_GL_H
#define N1_WINDOW_GL_H

#include "n1_window.h"

#if defined(__linux__)
#include "GL/glew.h"
#include <GL/glx.h>
#include <GL/gl.h>
#endif

struct n1_Window;

typedef struct n1_GLContext{
#if defined(__linux__)
  GLXContext handle;
#endif

  int32_t major;
  int32_t minor;
  
} n1_GLContext;

int  platform_create_glcontext(struct n1_Window* window);
void platform_window_swap_glbuffers(struct n1_Window* window);

#endif
