#ifndef N1_FILE_SYSTEM_H
#define N1_FILE_SYSTEM_H

#include "c_allocator/n1_allocator.h"

typedef struct FileContent{
  size_t size;
  void*  data;
} FileContent;

FileContent read_entire_file(const char* file_path, n1_Allocator allocator);

#endif
