#ifndef N1_WINDOW_H
#define N1_WINDOW_H


#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)      
#include <X11/Xlib.h>
#endif
#include <stdint.h>

#include "window/n1_window_gl.h"
#include "thread/n1_mutex.h"

typedef struct n1_Window{
  
#if defined(__linux__)
  Window       handle;
  Display*     display;
  VisualID     visual_id;
  n1_Mutex     mutex;
  n1_GLContext gl_context;
#endif
  int a;
} n1_Window;

n1_Window* platform_create_window(const char* title);
void       platform_free_window(n1_Window* window);
void       platform_window_swap_buffers(n1_Window* window);

#endif
