#ifndef N1_FENCE_H
#define N1_FENCE_H

typedef struct n1_Fence{

#if defined(_WIN32)

  HANDLE handle;
#elif defined(__linux__)

  n1_Mutex mutex;
  pthread_cond_t cond;
#endif

} n1_Fence;


n1_Fence platform_create_fence();
void     platform_free_fence(n1_Fence* fence);
void     platform_signal_fence(n1_Fence* fence);
void     platform_wait_fence(n1_Fence* fence);

#endif
