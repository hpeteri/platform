#include "time/n1_time.h"

#if defined (__linux__)
#include "n1_time_linux.c"
#endif

//__rdtsc()
#include <x86intrin.h>

uint64_t platform_get_cycle_counter(){
    return __rdtsc();
}

double   platform_convert_micros_to_seconds(uint64_t micro){
  return micro / (double)second_to_micros;
}

double   platform_convert_ns_to_seconds(uint64_t ns){
  return ns / (double)second_to_ns;
}

