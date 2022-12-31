#ifndef N1_WINDOW_EVENT_H
#define N1_WINDOW_EVENT_H

#define PLATFORM_MAX_WINDOW_EVENT_COUNT (256)

#include <stdint.h>
typedef enum PLATFORM_WINDDOW_EVENT_TYPE{
  EVENT_INVALID = 0,
  EVENT_CHAR,
  EVENT_KEY_DOWN,
  EVENT_KEY_UP,
  EVENT_SIZE,
  EVENT_MOUSE_DOWN,
  EVENT_MOUSE_UP,
  EVENT_MOUSE_WHEEL,
  EVENT_MOUSE_MOVE,
  EVENT_QUIT,
  
} PLATFORM_WINDOW_EVENT_TYPE;


typedef struct n1_WindowEvent{
  PLATFORM_WINDOW_EVENT_TYPE type;
  union {

    struct{
      uint32_t keycode;
    } key;

    struct{
      int32_t width;
      int32_t height;
    } size;
    
    struct {
      int32_t distance;
    } mouseWheel;

    struct {
      int32_t x;
      int32_t y;
    } mouse;
  };
} n1_WindowEvent;

typedef struct n1_WindowEventBuffer{
  int count;
  
  //extra space for non repeating events that are added when buffers get swapped
  n1_WindowEvent events[PLATFORM_MAX_WINDOW_EVENT_COUNT + 10];

  n1_WindowEvent size_event; 
    
} n1_WindowEventBuffer;

#endif
