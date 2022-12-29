#include "window/n1_window.h"

#include <stdlib.h>
#include <string.h>

#include "thread/n1_thread.h"
#include "thread/n1_mutex.h"
#include "thread/n1_fence.h"

typedef struct WindowCreationArgs{
  const char* title;
  n1_Window*  window;
  n1_Fence*   fence;
} WindowCreationArgs;


#if defined(_WIN32)
#include "n1_window_win32.c"
#elif defined(__linux__)
#include "n1_window_linux.c"
#include "n1_window_gl_linux.c"
#endif


n1_Window* platform_create_window(const char* title){
  n1_Window* window = (n1_Window*)malloc(sizeof(n1_Window));
  memset(window, 0, sizeof(*window));
    
  window->mutex = platform_create_mutex();
    
  n1_Fence fence = platform_create_fence();
  
  WindowCreationArgs args = {
    title,
    window,
    &fence};
  
  //Create a window from an another thread
  n1_Thread thread = platform_create_thread((platform_thread_proc)platform_create_window_2,
                                            &args);
    
  if(!thread.handle){
    return window;
  }
  
  //wait for window to be created
  platform_wait_fence(&fence);
  platform_free_fence(&fence);

  return window;
}

void platform_free_window(n1_Window* window){
  free(window);
}

void platform_window_swap_buffers(n1_Window* window){
  if(window->gl_context.handle){
    platform_window_swap_glbuffers(window);
  }
}
