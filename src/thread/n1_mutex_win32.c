#include <windows.h>

n1_Mutex platform_create_mutex(){
  n1_Mutex mutex;
  
  HANDLE handle = CreateMutex(NULL,
                              FALSE,
                              NULL);
  mutex.handle = handle;
  return mutex;
}

void platform_free_mutex(n1_Mutex* mutex){
  if(mutex->handle){
    CloseHandle(mutex->handle);
    mutex->handle = NULL;
  }
}

void platform_lock_mutex(n1_Mutex* mutex){
  if(mutex->handle){
    WaitForSingleObject(mutex->handle, INFINITE);
  }
}

void platform_unlock_mutex(n1_Mutex* mutex){
  if(mutex->handle){
    ReleaseMutex(mutex->handle);
  }
}

