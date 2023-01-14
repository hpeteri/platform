#include <windows.h>

n1_Fence platform_create_fence(){
  n1_Fence fence;
  
  HANDLE handle = CreateEvent(NULL, FALSE, FALSE, NULL);

  fence.handle = handle;
  return fence;
}

void platform_free_fence(n1_Fence* fence){
  if(fence->handle != NULL){
    CloseHandle(fence->handle);
    fence->handle = NULL;
  }
}

void platform_signal_fence(n1_Fence* fence){
  if(fence->handle != NULL){
    SetEvent(fence->handle);
  }
}

void platform_wait_fence(n1_Fence* fence){
  if(fence->handle != NULL){
    WaitForSingleObject(fence->handle, INFINITE);
  }
}
