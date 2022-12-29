#include <string.h>

n1_Mutex platform_create_mutex(){
  n1_Mutex mutex;
  
  pthread_mutex_init(&mutex.handle, NULL);
  return mutex;
}

void platform_free_mutex(n1_Mutex* mutex){
  pthread_mutex_destroy(&mutex->handle);
  memset(mutex, 0, sizeof(*mutex));
}

void platform_lock_mutex(n1_Mutex* mutex){
  pthread_mutex_lock(&mutex->handle);
}

void platform_unlock_mutex(n1_Mutex* mutex){
  pthread_mutex_unlock(&mutex->handle);
}
