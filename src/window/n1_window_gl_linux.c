
#include <GL/glx.h>
#include <GL/gl.h>

#include "GL/glew.h"


typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*,
                                                     GLXFBConfig,
                                                     GLXContext,
                                                     int,
                                                     const int*);

int platform_create_glcontext(n1_Window* window){
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
  GLXFBConfig* configs = glXChooseFBConfig(display,
                                           DefaultScreen(display),
                                           glxAttribs,
                                           &conf_count);
   
  XVisualInfo* visual = glXGetVisualFromFBConfig(display, configs[selectedConf]);
    
    
    
  GLXContext temp_gl_context = glXCreateNewContext(display, configs[selectedConf], GLX_RGBA_TYPE, 0, 1);

  if(!visual){
    return 0;
  }
  printf("Created context\n");
  glXMakeCurrent(display, window_handle, temp_gl_context);

  if(glewInit() != GLEW_OK){
    printf("Failed To init glew\n");
    return 0;
  }

  /////////////////////////////////////////////////////////////////////
  //Create 3.2 context
    
  glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
  glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");

  
  if(glXCreateContextAttribsARB){
    int contextAttributes[] = {
      GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
      GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        
      None
    };
    GLXContext context = 0;
    context = glXCreateContextAttribsARB(
                                         display,
                                         configs[selectedConf],
                                         0,
                                         1,
                                         contextAttributes
                                         );
    if(context){
      printf("Got 3.2 context\n");
      glXMakeCurrent(display, window_handle, context);
      glXDestroyContext(display, temp_gl_context);

      window->gl_context.handle = context;
      window->gl_context.major  = 3;
      window->gl_context.minor  = 2;

    }else{
      printf("Using legacy context\n");
      
      window->gl_context.handle = temp_gl_context;
    }
  }
  
  XFree(configs);
  return 1;
}
void platform_window_swap_glbuffers(n1_Window* window){
  glXSwapBuffers(window->display, window->handle);
}
