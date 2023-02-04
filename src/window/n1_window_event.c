#include "n1_window_event.h"
#include <stdio.h>

static void platform_window_push_new_event(n1_Window* window, n1_WindowEvent event);
static void platform_window_push_event(n1_Window* window, n1_WindowEvent event);
static void platform_window_swap_event_buffers(n1_Window* window);

static void platform_window_push_new_event(n1_Window* window, n1_WindowEvent event){
  if(!event.type){
    return;
  }
  window->event_buffer_swap.events[window->event_buffer_swap.count] = event;
  window->event_buffer_swap.count++;
}

static void platform_window_push_event(n1_Window* window, n1_WindowEvent event){
  platform_lock_mutex(&window->mutex);
  if(window->event_buffer_swap.count == PLATFORM_MAX_WINDOW_EVENT_COUNT){
    printf("Window event buffer is full. Not pushing event\n");
    
  }else{
    switch(event.type){
    case EVENT_SIZE:
      {
        window->event_buffer_swap.size_event = event;
        break;
      }
    default:
      {
        //repeating events
        platform_window_push_new_event(window, event);
        break;
      }
    }
  }
  platform_unlock_mutex(&window->mutex);
}

static void platform_window_swap_event_buffers(n1_Window* window){
  platform_lock_mutex(&window->mutex);

  //push non repeating events to buffer
  //extra space in reserved for non repeating events in the buffer.
  if(window->event_buffer_swap.size_event.type != 0){
    n1_WindowEvent event = window->event_buffer_swap.size_event;
    platform_window_push_new_event(window, event);
    
    window->width  = event.size.width  >  1 ? event.size.width  : 1;
    window->height = event.size.height >  1 ? event.size.height : 1;
  }
  //swap
  n1_WindowEventBuffer temp = window->event_buffer;
  window->event_buffer = window->event_buffer_swap;
  window->event_buffer_swap = temp;

  //reset 
  window->event_buffer_swap.count           = 0;
  window->event_buffer_swap.size_event.type = 0;
  
  platform_unlock_mutex(&window->mutex);
}
