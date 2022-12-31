#include <stdio.h>


#include "n1_platform_main.c"
#include "n1_platform.h"

int main(int argc, const char* argv[]){
  printf("hello, sailor!\n");

  n1_Window* window = platform_create_window("simple window");
  if(!platform_create_glcontext(window, 3, 2, 0)){
    perror("failed to create glContext\n");
    return 1;
  }
  
  uint64_t ns_start = platform_get_time_ns();
  uint64_t ms_start = platform_get_time_micros();

  int ns_fps = 0;
  int ms_fps = 0;
  int idx    = 0;

  int is_running = 1;
  while(is_running){

    //handle window events
    platform_window_get_events(window);

    n1_WindowEvent e = platform_window_get_next_event(window);
    while(e.type){
      printf("-> handle %d event\n", e.type);
      if(e.type == EVENT_QUIT){
        printf("quit\n");
        is_running = 0;
      }
      e = platform_window_get_next_event(window);
    }

    
    ns_fps ++;
    ms_fps ++;
    idx ++;
    
    glClearColor((idx % 255) / 255.0f, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    platform_window_swap_buffers(window);

    uint64_t ns_end = platform_get_time_ns();
    uint64_t ms_end = platform_get_time_micros();
    
    if(platform_convert_micros_to_seconds(ms_end - ms_start) >= 1){
      ms_start += second_to_micros;
      printf("ms 1 second passed :: %d\n", ms_fps);
      ms_fps = 0;
    }
    
    if(platform_convert_ns_to_seconds(ns_end - ns_start) >= 1){
      ns_start += second_to_ns;
      printf("ns 1 second passed :: %d\n", ns_fps);
      ns_fps = 0;
          
    }
  }
  
  platform_free_glcontext(window);  
  platform_free_window(window);
  return 0;
}

