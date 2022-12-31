#include <sys/resource.h>

size_t get_process_mem_use(){
  struct rusage r_usage; 
  getrusage(RUSAGE_SELF,&r_usage); 
 
  return r_usage.ru_maxrss;
}
