#ifndef N1_MUTEX_H
#define N1_MUTEX_H


#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <pthread.h>
#endif


typedef struct n1_Mutex{    
#if defined(_WIN32)
  HANDLE          handle;
#elif defined(__linux__)
  pthread_mutex_t handle;
#endif
} n1_Mutex;

n1_Mutex platform_create_mutex();
void     platform_free_mutex(n1_Mutex* mutex);
void     platform_lock_mutex(n1_Mutex* mutex);
void     platform_unlock_mutex(n1_Mutex* mutex);

#endif
