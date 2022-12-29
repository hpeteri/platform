static void* platform_create_window_2(WindowCreationArgs* args){
  n1_Window*  window = args->window;
  const char* title  = args->title;
  n1_Fence*      fence  = args->fence;

  XInitThreads();

  Display* display = XOpenDisplay(NULL);

  if(!display){
    platform_signal_fence(fence);
    return NULL;
  }

  Screen* screen   = DefaultScreenOfDisplay(display);
  int     screenId = DefaultScreen(display);

  //setup window attribs
  XSetWindowAttributes windowAttribs;
  windowAttribs.border_pixel      = BlackPixel(display, screenId);
  windowAttribs.background_pixel  = WhitePixel(display, screenId);
  windowAttribs.override_redirect = 1;
  windowAttribs.colormap          = XCreateColormap(display,
                                                    RootWindow(display, screenId),
                                                    XDefaultVisual(display, screenId),
                                                    AllocNone);
  windowAttribs.event_mask        = ExposureMask;
    
  Window w = XCreateWindow(display,
                           RootWindow(display, screenId),
                           0, 0,
                           400, 400,
                           0,
                           XDefaultDepth(display, screenId),
                           InputOutput,
                           XDefaultVisual(display, screenId),
                           CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
                           &windowAttribs);
    
  XStoreName(display, w, title);

  {
    Visual* default_visual = XDefaultVisual(display, screenId);
            
    VisualID visual_id = default_visual->visualid;
    window->visual_id = visual_id;
  }
    
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
        
      //HandleEvent(window, e);
      if(e.type == ClientMessage)
        break;
    }
  }
  return 0;
}

