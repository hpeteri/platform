#ifndef N1_TIME_H
#define N1_TIME_H

#define second_to_micros (1000000)
#define second_to_ns     (1000000000)

#include <stdint.h>

uint64_t platform_get_cycle_counter();
void     platform_init_time();
uint64_t platform_get_time_micros();
uint64_t platform_get_time_ns();
double   platform_convert_micros_to_seconds(uint64_t micro);
double   platform_convert_ns_to_seconds(uint64_t ns);


#endif
