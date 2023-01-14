#include <windows.h>

#include "n1_window_event.c"
#include "n1_window_keycode.h"

n1_Window* global_window;

LRESULT CALLBACK window_callback(HWND window,
                                 UINT message,
                                 WPARAM wParam,
                                 LPARAM lParam){
  LRESULT result = 0;
  
  switch(message){
  case WM_PAINT:
    {
      PAINTSTRUCT paint = {0};
      BeginPaint(window,&paint);
      EndPaint(window,&paint);
      break;
    }
  case WM_ERASEBKGND: 
    return TRUE; 
  case WM_DESTROY:
    //pass
  case WM_CLOSE:
    {
      
      n1_WindowEvent e = {.type = EVENT_QUIT};
      platform_window_push_event(global_window, e);
      break;
    }
  case WM_CHAR:
    {
      n1_WindowEvent e;
      e.type = EVENT_CHAR;
      e.key.keycode = (char)wParam;
      platform_window_push_event(global_window, e);
      break;
    }
  case WM_MOUSEMOVE:
    {
      int y = (int)(lParam >> 16); 
      int x = (int)(lParam & 0x0000ffff); 
        
      n1_WindowEvent e;
      e.type    = EVENT_MOUSE_MOVE;
      e.mouse.x = x; 
      e.mouse.y = y;
      
      platform_window_push_event(global_window, e);
      break;
    }
  case WM_MOUSEWHEEL:
    {
      n1_WindowEvent e;
      e.type                = EVENT_MOUSE_WHEEL;
      e.mouseWheel.distance = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;

      platform_window_push_event(global_window, e);
      break;
    }
  case WM_SIZE:
    {
      RECT client; 
      GetClientRect(window,&client); 

      n1_WindowEvent e;
      e.type        = EVENT_SIZE;
      e.size.width  = client.right;
      e.size.height = client.bottom;

      platform_window_push_event(global_window, e);
      break;
    }
  case WM_KEYDOWN:
  case WM_KEYUP:
    {
      n1_WindowEvent e;
      
      int was_down = lParam & (1 << 30); 
      if(was_down && message == WM_KEYDOWN)
          break; 
      
      e.type        = (message == WM_KEYUP)? EVENT_KEY_UP : EVENT_KEY_DOWN; 
      e.key.keycode = (unsigned short)wParam;
      
      platform_window_push_event(global_window, e);
      break;
    }
  case WM_LBUTTONUP:
  case WM_LBUTTONDOWN:
    {
      n1_WindowEvent e;
       
      int was_down = lParam & (1 << 30); 
      if(was_down && message == WM_KEYDOWN)
        break; 
      
      e.type        = (message == WM_LBUTTONUP)? EVENT_MOUSE_UP : EVENT_MOUSE_DOWN; 
      e.key.keycode = 1; 

      platform_window_push_event(global_window, e);
      break;
    }
  case WM_RBUTTONUP:
  case WM_RBUTTONDOWN:
    {
      
      n1_WindowEvent e;
       
      int was_down = lParam & (1 << 30); 
      if(was_down && message == WM_KEYDOWN)
        break; 
      
      e.type        = (message == WM_RBUTTONUP)? EVENT_MOUSE_UP : EVENT_MOUSE_DOWN; 
      e.key.keycode = 3; 

      platform_window_push_event(global_window, e);
      break;
    }
  default:
    {
      result = DefWindowProc(window, message, wParam, lParam);  
      break;
    }
      
  };
    
  return result;
}

static void* platform_create_window_2(WindowCreationArgs* args){
  n1_Window*  window = args->window;
  const char* title  = args->title;
  n1_Fence*   fence  = args->fence;
  const int   width  = args->width;
  const int   height = args->height;  

  if(global_window){
    // we currently can handle 1 window...
    *(int*)NULL = 0;
    
  }
  global_window = window;
  
  HINSTANCE hinstance = GetModuleHandle(NULL);

  // register window class
  WNDCLASSEX window_class = {
    .cbSize              = sizeof(WNDCLASSEX),
    .style               = CS_HREDRAW|CS_VREDRAW,
    .lpfnWndProc         = window_callback,
    .cbClsExtra          = 0,
    .cbWndExtra          = 0,
    .hInstance           = hinstance,
    .hIcon               = NULL,
    .hCursor             = NULL,
    .hbrBackground       = (HBRUSH)(COLOR_WINDOW + 1),
    .lpszClassName       = "WINDOW",
  };

  if(!RegisterClassEx(&window_class)){
    perror("failed to register window class\n");
    goto cleanup_on_error;
  }

  // create window
  window->handle = CreateWindow(window_class.lpszClassName,   //                      
                                title,                        //                      
                                WS_OVERLAPPEDWINDOW,          //                      
                                CW_USEDEFAULT,                // x
                                CW_USEDEFAULT,                // y
                                width,                        // width                    
                                height,                       // height                
                                NULL,                         // parent                     
                                NULL,                         // menu               
                                hinstance,                    // instance                 
                                NULL);                        // param                     

  if(window->handle == NULL){
    perror("failed to create window\n");
    goto cleanup_on_error;
  }
    
  window->hinstance = hinstance;
  window->hdc       = GetDC(window->handle);
    
  

  ShowWindow(window->handle, SW_SHOW);  
  if(!UpdateWindow(window->handle)){
    perror("failed to update window");
    goto cleanup_on_error;
  }

  RECT client;
  GetClientRect(window->handle, &client);
  ValidateRect(window->handle, &client);

  // signal main thread that window is ready
  platform_signal_fence(fence);

  MSG msg;
  for(;;){
    if(PeekMessage(&msg,0,0,0,PM_REMOVE)){
      if(msg.message == WM_QUIT){
        n1_WindowEvent e;
        e.type = EVENT_QUIT;
        platform_window_push_event(global_window, e);
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    WaitMessage();
  }
  
  if(0){
    
  cleanup_on_error:
    platform_signal_fence(fence);

  }
  global_window = NULL;
  return NULL;
}

static void platform_free_window_2(n1_Window* window){
  ReleaseDC(window->handle, window->hdc);
}
