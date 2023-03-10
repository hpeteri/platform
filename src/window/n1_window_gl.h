#ifndef N1_WINDOW_GL_H
#define N1_WINDOW_GL_H

#include "n1_window.h"

#if defined (_WIN32)

#define GLEW_STATIC
#include "GL/glew.h"
#include <GL/wglew.h>

#include <GL/gl.h>

#elif defined (__linux__)

#define GLEW_STATIC
#include "GL/glew.h"
#include <GL/glx.h>
#include <GL/gl.h>

#endif

struct n1_Window;

typedef struct n1_GLContext{

#if defined(_WIN32)

  HGLRC handle;
  
#elif defined(__linux__)

  GLXContext handle;
  
#endif

  int32_t major;
  int32_t minor;
  
} n1_GLContext;

int init_gl_proc_addresses();

int  platform_create_glcontext(struct n1_Window* window, int major, int minor, int debug);
void platform_free_glcontext(struct n1_Window* window);
void platform_window_swap_glbuffers(struct n1_Window* window);

int platform_gl_swap_interval(int i);


#endif
