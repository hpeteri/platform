#include <windows.h>
#include <wingdi.h>


#define GLEW_STATIC
#include "GL/glew.h"

#include <GL/GL.h>
#include "GL/wglew.h"

int platform_create_glcontext(struct n1_Window* window, int major, int minor, int debug){
  HDC hdc = window->hdc;

  PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
    PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
    32,                   // Colordepth of the framebuffer.
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0, 0, 0, 0,
    24,                   // Number of bits for the depthbuffer
    8,                    // Number of bits for the stencilbuffer
    0,                    // Number of Aux buffers in the framebuffer.
    PFD_MAIN_PLANE,
    0,
    0, 0, 0
  };

  PIXELFORMATDESCRIPTOR given_pdf;
  int given_pdf_idx = ChoosePixelFormat(hdc, &pfd);

  if(!SetPixelFormat(hdc, given_pdf_idx, &given_pdf)){
    return 0;
  }

  HGLRC temp_gl_context = wglCreateContext(hdc);

  if(!wglMakeCurrent(hdc, temp_gl_context)){
    MessageBox(window->handle, "failed to initialize opengl.", "ERROR", MB_ICONERROR);
    //@LEAK CONTEXT
    return 0;
  }
  
  if(glewInit() != GLEW_OK){
    MessageBox(NULL, "failed to initialize glew.", "ERROR", MB_ICONERROR);
    //@LEAK CONTEXT
    return 0;
  }

  // create actual context we want
  
  const int pixel_format_attribs[] = {
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 24,
    WGL_STENCIL_BITS_ARB, 8,
    0 // End of attributes list
  };

  int context_attribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, major,
    WGL_CONTEXT_MINOR_VERSION_ARB, minor,
    
    WGL_CONTEXT_FLAGS_ARB,
    debug ? WGL_CONTEXT_DEBUG_BIT_ARB | WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB   :  WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
      
    WGL_CONTEXT_PROFILE_MASK_ARB,
    WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0
  };
    
  int  pixel_format = 0;
  unsigned int format_count = 0;
    
  wglChoosePixelFormatARB(hdc, pixel_format_attribs, NULL, 1, &pixel_format, &format_count);
    
  SetPixelFormat(hdc, pixel_format, &pfd);
    
  HGLRC gl_context = wglCreateContextAttribsARB(hdc, 0, context_attribs);
 
  if(!wglMakeCurrent(hdc, gl_context)){
    MessageBox(NULL,"failed to create wanted opengl context. ", "ERROR", MB_ICONERROR);
    return 0;
  }
  
  wglDeleteContext(temp_gl_context);
  
  window->gl_context.handle = gl_context;
  window->gl_context.major  = major;
  window->gl_context.minor  = minor;
  
  return 1;
}

void platform_free_glcontext(struct n1_Window* window){
  wglDeleteContext(window->gl_context.handle);
}

void platform_window_swap_glbuffers(n1_Window* window){
  SwapBuffers(window->hdc);
}

int platform_gl_swap_interval(int i){
  return 1;
}
