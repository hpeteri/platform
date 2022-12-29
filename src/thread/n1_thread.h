#ifndef N1_THREAD_H
#define N1_THREAD_H

#if defined(_WIN32)

#elif defined(__linux__)
typedef void* (*platform_thread_proc)(void*);
typedef pthread_t ThreadID;
#endif

typedef struct n1_Thread{
#if defined(_WIN32)
  HANDLE handle;
#elif defined(__linux__)
  pthread_t handle;
#endif
} n1_Thread;

n1_Thread platform_create_thread(platform_thread_proc thread_proc, void* args);
void      platform_free_thread(n1_Thread* thread);
void      platform_thread_join(n1_Thread* thread);
ThreadID  platform_get_thread_id();


#endif
