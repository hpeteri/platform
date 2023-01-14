#include "time/n1_time.h"

#if defined (_WIN32)

#include "n1_time_win32.c"

#elif defined (__linux__)

#include "n1_time_linux.c"

#endif


// include for __rdtsc

#if defined(_MSC_VER)

#include <intrin.h>

#elif defined(__GNUC__)

#include <x86intrin.h>

#endif


uint64_t platform_get_cycle_counter(){
    return __rdtsc();
}

double platform_convert_micros_to_seconds(uint64_t micro){
  return micro / (double)second_to_micros;
}

double platform_convert_ns_to_seconds(uint64_t ns){
  return ns / (double)second_to_ns;
}

