n1_Fence platform_create_fence(){
  n1_Fence fence;
  fence.mutex = platform_create_mutex();
  pthread_cond_init(&fence.cond, NULL);

  return fence;
}

void platform_free_fence(n1_Fence* fence){
  platform_free_mutex(&fence->mutex);
}

void platform_signal_fence(n1_Fence* fence){
  pthread_cond_broadcast(&fence->cond);
}

void platform_wait_fence(n1_Fence* fence){
  platform_lock_mutex(&fence->mutex);
  pthread_cond_wait(&fence->cond, &fence->mutex.handle);
}
