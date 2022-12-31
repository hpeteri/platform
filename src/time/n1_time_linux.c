#include "n1_time.h"

#include <sys/times.h>
#include <time.h>

void platform_init_time(){
  //pass
}

uint64_t platform_get_time_micros(){
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);
  
  return (t.tv_sec * second_to_micros) + (t.tv_nsec / 1000);
}

uint64_t platform_get_time_ns(){
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);

  return (t.tv_sec * second_to_ns) + (t.tv_nsec);
}
