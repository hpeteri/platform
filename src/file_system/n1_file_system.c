#include "n1_file_system.h"

#if defined (_WIN32)

#include "n1_file_system_win32.c"

#elif defined (__linux__)

#include "n1_file_system_linux.c"

#endif
