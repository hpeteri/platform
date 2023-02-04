#include <pthread.h>

n1_Thread platform_create_thread(platform_thread_proc thread_proc, void* args){
  n1_Thread thread;
  
  pthread_create(&thread.handle, NULL, thread_proc, args);
  return thread;
}

void platform_free_thread(n1_Thread* thread){
  if(!thread->handle)
    return;
  
  pthread_cancel(thread->handle);
  pthread_join(thread->handle, NULL);

  thread->handle = 0;
}

void platform_thread_join(n1_Thread* thread){
  pthread_join(thread->handle, NULL);
}

ThreadID  platform_get_thread_id(){
  return  pthread_self();
}
