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

#include "window/n1_window_event.h"
#include "window/n1_window_keycode.h"

typedef struct n1_Window{

#if defined(_WIN32)
  HANDLE    handle;
  HINSTANCE hinstance;
  HDC       hdc;

#elif defined(__linux__)
  Window       handle;
  Display*     display;
  VisualID     visual_id;
#endif

  n1_Mutex     mutex;
  n1_GLContext gl_context;

  int                  event_idx;
  n1_WindowEventBuffer event_buffer;
  n1_WindowEventBuffer event_buffer_swap;

  //updated when platform_window_get_events is called().
  int32_t width;
  int32_t height;
} n1_Window;

n1_Window*     platform_create_window(const char* title, int width, int height);
void           platform_free_window(n1_Window* window);
void           platform_window_swap_buffers(n1_Window* window);
void           platform_window_get_events(n1_Window* window);
n1_WindowEvent platform_window_get_next_event(n1_Window* window);

#endif
