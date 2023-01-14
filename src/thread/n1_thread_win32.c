#include <windows.h>

n1_Thread platform_create_thread(platform_thread_proc thread_proc, void* args){
  n1_Thread thread;

  DWORD id;
  HANDLE handle = CreateThread(NULL,
                               0,
                               thread_proc,
                               args,
                               0,
                               &id);
  
  thread.handle = handle;
  return thread;
}

void platform_free_thread(n1_Thread* thread){
  if(thread->handle == NULL)
    return;
  
  BOOL success = TerminateThread(thread->handle, 0);
  CloseHandle(thread->handle);
    
  thread->handle = NULL;
}

void platform_thread_join(n1_Thread* thread){
  if(thread->handle == NULL)
    return;

  WaitForSingleObject(thread->handle, INFINITE);
}

ThreadID platform_get_thread_id(){
  return GetCurrentThreadId();
}
