#include "n1_window_event.c"
#include "n1_window_keycode.h"

#include "X11/keysymdef.h"

//keycodes are in upper case
static uint16_t upper_case(uint16_t c){
  if(c >= 'a' && c <= 'z'){
    c -= 'a' - 'A';
  }
  return c;
}

static int map_xkeysym_to_kc(uint16_t sym){

  switch(sym){
  //case(): return KC_LBUTTON                         ;
  //case(): return KC_RBUTTON                         ;
  //case(): return KC_CANCEL                          ;
  //case(): return KC_MBUTTON                         ;    
  //case(): return KC_XBUTTON1                        ;    
  //case(): return KC_XBUTTON2                        ;    
  case(XK_BackSpace): return KC_BACK                            ;
  case(XK_Tab):       return KC_TAB                             ;
  case(XK_Clear):     return KC_CLEAR                           ;
  case(XK_Return):    return KC_RETURN                          ;
  //case(): return KC_SHIFT                           ;
  //case(): return KC_CONTROL                         ;
  //case(): return KC_MENU                            ;
  case(XK_Pause): return KC_PAUSE                           ;
  case(XK_Caps_Lock): return KC_CAPITAL                         ;
  //case(): return KC_KANA                            ;
  //case(): return KC_HANGEUL                         ;  
  //case(): return KC_HANGUL                          ;
  //case(): return KC_JUNJA                           ;
  //case(): return KC_FINAL                           ;
  //case(): return KC_HANJA                           ;
  //case(): return KC_KANJI                           ;
  case(XK_Escape): return KC_ESCAPE                          ;
  //case(): return KC_CONVERT                         ;
  //case(): return KC_NONCONVERT                      ;
  //case(): return KC_ACCEPT                          ;
  //case(): return KC_MODECHANGE                      ;
  case(XK_space): return KC_SPACE                           ;
  case(XK_Prior): return KC_PRIOR                           ;
  case(XK_Next): return KC_NEXT                            ;
  case(XK_End): return KC_END                             ;
  case(XK_Home): return KC_HOME                            ;
  case(XK_Left): return KC_LEFT                            ;
  case(XK_Up): return KC_UP                              ;
  case(XK_Right): return KC_RIGHT                           ;
  case(XK_Down): return KC_DOWN                            ;
  case(XK_Select): return KC_SELECT                          ;
  case(XK_Print): return KC_PRINT                           ;
  case(XK_Execute): return KC_EXECUTE                         ;
    //case(): return KC_SNAPSHOT                        ;
  case(XK_Insert): return KC_INSERT                          ;
  case(XK_Delete): return KC_DELETE                          ;
  case(XK_Help): return KC_HELP                            ;
  case(XK_Super_L): return KC_LWIN                            ;
  case(XK_Super_R): return KC_RWIN                            ;
  //case(): return KC_APPS                            ;
  //case(): return KC_SLEEP                           ;
  case(XK_KP_0): return KC_NUMPAD0                         ;
  case(XK_KP_1): return KC_NUMPAD1                         ;
  case(XK_KP_2): return KC_NUMPAD2                         ;
  case(XK_KP_3): return KC_NUMPAD3                         ;
  case(XK_KP_4): return KC_NUMPAD4                         ;
  case(XK_KP_5): return KC_NUMPAD5                         ;
  case(XK_KP_6): return KC_NUMPAD6                         ;
  case(XK_KP_7): return KC_NUMPAD7                         ;
  case(XK_KP_8): return KC_NUMPAD8                         ;
  case(XK_KP_9): return KC_NUMPAD9                         ;
  case(XK_KP_Multiply): return KC_MULTIPLY                        ;
  case(XK_KP_Add): return KC_ADD                             ;
  case(XK_KP_Separator): return KC_SEPARATOR                       ;
  case(XK_KP_Subtract): return KC_SUBTRACT                        ;
  case(XK_KP_Decimal): return KC_DECIMAL                         ;
  case(XK_KP_Divide): return KC_DIVIDE                          ;
  case(XK_F1): return KC_F1                              ;
  case(XK_F2): return KC_F2                              ;
  case(XK_F3): return KC_F3                              ;
  case(XK_F4): return KC_F4                              ;
  case(XK_F5): return KC_F5                              ;
  case(XK_F6): return KC_F6                              ;
  case(XK_F7): return KC_F7                              ;
  case(XK_F8): return KC_F8                              ;
  case(XK_F9): return KC_F9                              ;
  case(XK_F10): return KC_F10                             ;
  case(XK_F11): return KC_F11                             ;
  case(XK_F12): return KC_F12                             ;
  case(XK_F13): return KC_F13                             ;
  case(XK_F14): return KC_F14                             ;
  case(XK_F15): return KC_F15                             ;
  case(XK_F16): return KC_F16                             ;
  case(XK_F17): return KC_F17                             ;
  case(XK_F18): return KC_F18                             ;
  case(XK_F19): return KC_F19                             ;
  case(XK_F20): return KC_F20                             ;
  case(XK_F21): return KC_F21                             ;
  case(XK_F22): return KC_F22                             ;
  case(XK_F23): return KC_F23                             ;
  case(XK_F24): return KC_F24                             ;
  //case(): return KC_NAVIGATION_VIEW                 ;
  //case(): return KC_NAVIGATION_MENU                 ;
  //case(): return KC_NAVIGATION_UP                   ;
  //case(): return KC_NAVIGATION_DOWN                 ;
  //case(): return KC_NAVIGATION_LEFT                 ;
  //case(): return KC_NAVIGATION_RIGHT                ;
  //case(): return KC_NAVIGATION_ACCEPT               ;
  //case(): return KC_NAVIGATION_CANCEL               ;
  case(XK_Num_Lock): return KC_NUMLOCK                         ;
  case(XK_Scroll_Lock): return KC_SCROLL                          ;
  //case(): return KC_OEM_NEC_EQUAL                   ;   
  //case(): return KC_OEM_FJ_JISHO                    ;   
  //case(): return KC_OEM_FJ_MASSHOU                  ;   
  //case(): return KC_OEM_FJ_TOUROKU                  ;   
  //case(): return KC_OEM_FJ_LOYA                     ;   
  //case(): return KC_OEM_FJ_ROYA                     ;   
  case(XK_Shift_L): return KC_LSHIFT                          ;
  case(XK_Shift_R): return KC_RSHIFT                          ;
  case(XK_Control_L): return KC_LCONTROL                        ;
  case(XK_Control_R): return KC_RCONTROL                        ;
  case(XK_Alt_L): return KC_LMENU                           ;
  case(XK_Alt_R): return KC_RMENU                           ;
  //case(): return KC_BROWSER_BACK                    ;
  //case(): return KC_BROWSER_FORWARD                 ;
  //case(): return KC_BROWSER_REFRESH                 ;
  //case(): return KC_BROWSER_STOP                    ;
  //case(): return KC_BROWSER_SEARCH                  ;
  //case(): return KC_BROWSER_FAVORITES               ;
  //case(): return KC_BROWSER_HOME                    ;
  //case(): return KC_VOLUME_MUTE                     ;
  //case(): return KC_VOLUME_DOWN                     ;
  //case(): return KC_VOLUME_UP                       ;
  //case(): return KC_MEDIA_NEXT_TRACK                ;
  //case(): return KC_MEDIA_PREV_TRACK                ;
  //case(): return KC_MEDIA_STOP                      ;
  //case(): return KC_MEDIA_PLAY_PAUSE                ;
  //case(): return KC_LAUNCH_MAIL                     ;
  //case(): return KC_LAUNCH_MEDIA_SELECT             ;
  //case(): return KC_LAUNCH_APP1                     ;
  //case(): return KC_LAUNCH_APP2                     ;
  //case(): return KC_OEM_1                           ;
  //case(): return KC_OEM_PLUS                        ;
  //case(): return KC_OEM_COMMA                       ;
  //case(): return KC_OEM_MINUS                       ;
  //case(): return KC_OEM_PERIOD                      ;
  //case(): return KC_OEM_2                           ;
  //case(): return KC_OEM_3                           ;
  //case(): return KC_GAMEPAD_A                       ;
  //case(): return KC_GAMEPAD_B                       ;
  //case(): return KC_GAMEPAD_X                       ;
  //case(): return KC_GAMEPAD_Y                       ;
  //case(): return KC_GAMEPAD_RIGHT_SHOULDER          ;
  //case(): return KC_GAMEPAD_LEFT_SHOULDER           ;
  //case(): return KC_GAMEPAD_LEFT_TRIGGER            ;
  //case(): return KC_GAMEPAD_RIGHT_TRIGGER           ;
  //case(): return KC_GAMEPAD_DPAD_UP                 ;
  //case(): return KC_GAMEPAD_DPAD_DOWN               ;
  //case(): return KC_GAMEPAD_DPAD_LEFT               ;
  //case(): return KC_GAMEPAD_DPAD_RIGHT              ;
  //case(): return KC_GAMEPAD_MENU                    ;
  //case(): return KC_GAMEPAD_VIEW                    ;
  //case(): return KC_GAMEPAD_LEFT_THUMBSTICK_BUTTON  ;
  //case(): return KC_GAMEPAD_RIGHT_THUMBSTICK_BUTTON ;
  //case(): return KC_GAMEPAD_LEFT_THUMBSTICK_UP      ;
  //case(): return KC_GAMEPAD_LEFT_THUMBSTICK_DOWN    ;
  //case(): return KC_GAMEPAD_LEFT_THUMBSTICK_RIGHT   ;
  //case(): return KC_GAMEPAD_LEFT_THUMBSTICK_LEFT    ;
  //case(): return KC_GAMEPAD_RIGHT_THUMBSTICK_UP     ;
  //case(): return KC_GAMEPAD_RIGHT_THUMBSTICK_DOWN   ;
  //case(): return KC_GAMEPAD_RIGHT_THUMBSTICK_RIGHT  ;
  //case(): return KC_GAMEPAD_RIGHT_THUMBSTICK_LEFT   ;
  //case(): return KC_OEM_4                           ;
  //case(): return KC_OEM_5                           ;
  //case(): return KC_OEM_6                           ;
  //case(): return KC_OEM_7                           ;
  //case(): return KC_OEM_8                           ;
  //case(): return KC_OEM_AX                          ;
  //case(): return KC_OEM_102                         ;
  //case(): return KC_ICO_HELP                        ;
  //case(): return KC_ICO_00                          ;
  //case(): return KC_PROCESSKEY                      ;
  //case(): return KC_ICO_CLEAR                       ;
  //case(): return KC_PACKET                          ;
  //case(): return KC_OEM_RESET                       ;
  //case(): return KC_OEM_JUMP                        ;
  //case(): return KC_OEM_PA1                         ;
  //case(): return KC_OEM_PA2                         ;
  //case(): return KC_OEM_PA3                         ;
  //case(): return KC_OEM_WSCTRL                      ;
  //case(): return KC_OEM_CUSEL                       ;
  //case(): return KC_OEM_ATTN                        ;
  //case(): return KC_OEM_FINISH                      ;
  //case(): return KC_OEM_COPY                        ;
  //case(): return KC_OEM_AUTO                        ;
  //case(): return KC_OEM_ENLW                        ;
  //case(): return KC_OEM_BACKTAB                     ;
  //case(): return KC_ATTN                            ;
  //case(): return KC_CRSEL                           ;
  //case(): return KC_EXSEL                           ;
  //case(): return KC_EREOF                           ;
  //case(): return KC_PLAY                            ;
  //case(): return KC_ZOOM                            ;
  //case(): return KC_NONAME                          ;
  //case(): return KC_PA1                             ;
  //case(): return KC_OEM_CLEAR                       ;
  }
  
  return sym;
}
void platform_handle_window_event(n1_Window* window, XEvent e){
  switch(e.type){
  case KeyPress:
    {
      KeySym baseKey = XLookupKeysym(&e.xkey, 0);
      KeySym charKey = XLookupKeysym(&e.xkey, e.xkey.state);

      n1_WindowEvent keyEvent = {};
      keyEvent.type = EVENT_KEY_DOWN;

      baseKey = upper_case(baseKey);
      keyEvent.key.keycode = map_xkeysym_to_kc(baseKey);

      platform_window_push_event(window, keyEvent);
        
        
      if(charKey != NoSymbol){
        //We should check if key has a symbol
        n1_WindowEvent charEvent = {};
        charEvent.type = EVENT_CHAR;
        charEvent.key.keycode = charKey;
        
        platform_window_push_event(window, charEvent);
      }
      break;
    } 
  case KeyRelease:
    {
      KeySym baseKey = XLookupKeysym(&e.xkey, 0);
       
      n1_WindowEvent keyEvent = {};
      keyEvent.type = EVENT_KEY_UP;

      baseKey = upper_case(baseKey);
      keyEvent.key.keycode = map_xkeysym_to_kc(baseKey);
      
      platform_window_push_event(window, keyEvent);
      break;
    }
  case ButtonPress:
    {
      n1_WindowEvent buttonEvent = {};
      buttonEvent.type = (e.xbutton.button < 4) ? EVENT_MOUSE_DOWN : EVENT_MOUSE_WHEEL;

      if(e.xbutton.button <= 3){
        buttonEvent.key.keycode = e.xbutton.button;
      }else{
        buttonEvent.mouseWheel.distance = (e.xbutton.button == 4) * 1 - (e.xbutton.button == 5) * 1;
      }
        
      platform_window_push_event(window, buttonEvent);
                
      break;
    }
  case ButtonRelease:
    {
      n1_WindowEvent buttonEvent = {};
      buttonEvent.type = EVENT_MOUSE_UP;
        
      if(e.xbutton.button <= 3){
        buttonEvent.key.keycode = e.xbutton.button;
        platform_window_push_event(window, buttonEvent);
      }        
                
      break;
    }
  case MotionNotify:
    {
      n1_WindowEvent event;
      event.type = EVENT_MOUSE_MOVE;
      event.mouse.x = e.xmotion.x;
      event.mouse.y = e.xmotion.y;
      
      platform_window_push_event(window, event);      
      break;
    }
  case EnterNotify:
    break;
  case LeaveNotify:
    break;
  case FocusIn:
    break;
  case FocusOut:
    break;
  case Expose:
    break;
  case GraphicsExpose:
    break;
  case NoExpose:
    break;
  case CirculateRequest:
    break;
  case ConfigureRequest:
    break;
  case MapRequest:
    break;
  case ResizeRequest:
    break;
  case CirculateNotify:
    break;
  case ConfigureNotify:
    n1_WindowEvent ev;
    ev.type = EVENT_SIZE;
    ev.size.width = e.xconfigure.width;
    ev.size.height = e.xconfigure.height;
    platform_window_push_event(window, ev);
    break;
  case CreateNotify:
    break;
  case DestroyNotify:
    break;
  case GravityNotify:
    break;
  case MapNotify:
    break;
  case MappingNotify:
    break;
  case ReparentNotify:
    break;
  case UnmapNotify:
    break;
  case VisibilityNotify:
    break;
  case ColormapNotify:
    break;
  case ClientMessage:
    n1_WindowEvent e = {.type = EVENT_QUIT};
    platform_window_push_event(window, e);
    break;
  case PropertyNotify:
    break;
  case SelectionClear:
    break;
  case SelectionNotify:
    break;
  case SelectionRequest:
    break;      
  default:
    break;
  }    
}

static void* platform_create_window_2(WindowCreationArgs* args){
  n1_Window*  window = args->window;
  const char* title  = args->title;
  n1_Fence*   fence  = args->fence;
  const int   width  = args->width;
  const int   height = args->height;

  //Xlib support for concurrent threads.
  //
  XInitThreads();

  //Open default display
  Display* display = XOpenDisplay(NULL);
  if(!display){
    platform_signal_fence(fence);
    return NULL;
  }

  Screen* screen         = DefaultScreenOfDisplay(display);
  int     screen_id      = DefaultScreen(display);
  Visual* default_visual = XDefaultVisual(display, screen_id);
  Window  root_window    = RootWindow(display, screen_id);
  
  {
    //set visual_id.
    //atleast vulkan surfaces need this
    VisualID visual_id = default_visual->visualid;
    window->visual_id = visual_id;
  }
  
  //setup window attribs
  XSetWindowAttributes windowAttribs;
  
  windowAttribs.border_pixel      = BlackPixel(display, screen_id);
  windowAttribs.background_pixel  = WhitePixel(display, screen_id);
  windowAttribs.override_redirect = 1;
  windowAttribs.colormap          = XCreateColormap(display,
                                                    root_window,
                                                    default_visual,
                                                    AllocNone);
  windowAttribs.event_mask        = ExposureMask;
    
  Window w = XCreateWindow(display,
                           root_window,
                           0, 0,
                           width, height,
                           0,
                           XDefaultDepth(display, screen_id),
                           InputOutput,
                           default_visual,
                           CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
                           &windowAttribs);
    
  XStoreName(display, w, title);

 
    
  VisualID visual_id = 0;
  window->handle    = w;
  window->display   = display;
    
  XSelectInput(display, w,
               KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask |
               LeaveWindowMask | PointerMotionMask | ButtonMotionMask | KeymapStateMask |
               StructureNotifyMask | FocusChangeMask | ExposureMask);
    
  //Prevent window from closing
  Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", 0);
  if(!XSetWMProtocols(display, w, &wm_delete_window, 1))
    perror("Protocol fail");

  
  XMapWindow(display, w);
  XFlush(display);

  //signal main thread that window is ready
  platform_signal_fence(fence);
      
  for(;;){
    if(XPending(display) > 0){
      XEvent e;
        
      XNextEvent(display, &e);
        
      platform_handle_window_event(window, e);
      if(e.type == ClientMessage)
        break;
    }
  }
  return 0;
}

static void platform_free_window_2(n1_Window* window){
  XDestroyWindow(window->display, window->handle);
  XCloseDisplay(window->display);
}
