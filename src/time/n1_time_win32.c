#include "n1_time.h"

#include <stdint.h>
static uint64_t n1_timestamp_win32_pfq;

void platform_init_time(){
  LARGE_INTEGER temp;
  QueryPerformanceFrequency(&temp);
  n1_timestamp_win32_pfq = temp.QuadPart;
}

uint64_t platform_get_time_micros(){
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (second_to_micros * now.QuadPart / n1_timestamp_win32_pfq);
}

uint64_t platform_get_time_ns(){
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (second_to_ns * now.QuadPart / n1_timestamp_win32_pfq);
}
