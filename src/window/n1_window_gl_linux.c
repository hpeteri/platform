
#include <GL/glx.h>
#include <GL/gl.h>

#include "GL/glew.h"


typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*,
                                                     GLXFBConfig,
                                                     GLXContext,
                                                     int,
                                                     const int*);

int  platform_create_glcontext(struct n1_Window* window, int major, int minor, int debug){
  Window   window_handle = window->handle;
  Display* display       = window->display;
  Screen*  screen        = DefaultScreenOfDisplay(display);
  int      screen_id     = DefaultScreen(display);
    
  GLint glxAttribs[] = {
    GLX_X_RENDERABLE    , True,
    GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
    GLX_RENDER_TYPE     , GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
    GLX_RED_SIZE        , 8,
    GLX_GREEN_SIZE      , 8,
    GLX_BLUE_SIZE       , 8,
    GLX_ALPHA_SIZE      , 8,
    GLX_DEPTH_SIZE      , 24,
    GLX_STENCIL_SIZE    , 8,
    GLX_DOUBLEBUFFER    , True,
    None
  };

  int conf_count;
  int selectedConf = 0;

  //@TODO
  //we should actually select a combatible visual. Currently we just pick the first one. without 
  GLXFBConfig* configs = glXChooseFBConfig(display,
                                           DefaultScreen(display),
                                           glxAttribs,
                                           &conf_count);
   
  XVisualInfo* visual = glXGetVisualFromFBConfig(display, configs[selectedConf]);
    
    
  // create temporary context since glXCreateContextARB requires glXContext to be active.
  GLXContext temp_gl_context = glXCreateNewContext(display, configs[selectedConf], GLX_RGBA_TYPE, 0, 1);

  if(!visual){
    return 0;
  }
    
  if(!glXMakeCurrent(display, window_handle, temp_gl_context)){
    perror("glxMakeCurrent() failed: ");
    asm("int3");
    return 0;
  }else{
  
  }
  
  if(glewInit() != GLEW_OK){
    printf("Failed To init glew\n");
    return 0;
  }

  // create glx context
  glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
  glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");

  // if func not found, return the default context
  if(glXCreateContextAttribsARB){
    int contextAttributes[] = {
      GLX_CONTEXT_MAJOR_VERSION_ARB, major,
      GLX_CONTEXT_MINOR_VERSION_ARB, minor,

      GLX_CONTEXT_FLAGS_ARB,
      debug ? GLX_CONTEXT_DEBUG_BIT_ARB | GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB   :  GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
      
      GLX_CONTEXT_PROFILE_MASK_ARB,
      GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
      None
    };
    
    GLXContext context = 0;
    context = glXCreateContextAttribsARB(display,
                                         configs[selectedConf],
                                         0,
                                         1,
                                         contextAttributes
                                         );
    if(context){
      
      glXMakeCurrent(display, window_handle, context);

      glXDestroyContext(display, temp_gl_context);
      
      window->gl_context.handle = context;
      window->gl_context.major  = major;
      window->gl_context.minor  = minor;
      
    }else{      

      window->gl_context.handle = temp_gl_context;

    }
  }else{
    // failed to get glXCreateContextAttribsARB proc.
    // use the default glxContext.
    window->gl_context.handle = temp_gl_context;
  }
  
  XFree(configs);
  return 1;
}

void platform_free_glcontext(struct n1_Window* window){
  glXDestroyContext(window->display, window->gl_context.handle);
}

void platform_window_swap_glbuffers(n1_Window* window){
  glXSwapBuffers(window->display, window->handle);
}

int platform_gl_swap_interval(int i){

  static void (*glXSwapIntervalEXT)(Display *, GLXDrawable, int);

  if(!glXSwapIntervalEXT){
    glXSwapIntervalEXT = (void(*)(Display*, GLXDrawable, int))glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalEXT");
  }

  
  if(glXSwapIntervalEXT){
    
    Display     *dpy      = glXGetCurrentDisplay();
    GLXDrawable  drawable = glXGetCurrentDrawable();
  
    if(drawable){
      glXSwapIntervalEXT(dpy, drawable, i);
      return 0;
    }
  }
  return 1;
}
