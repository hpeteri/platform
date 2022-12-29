#include "n1_thread.h"
#include "n1_mutex.h"
#include "n1_fence.h"

#if defined(_WIN32)
#include "n1_thread_win32.c"
#include "n1_mutex_win32.c"
#elif defined(__linux__)
#include "n1_thread_linux.c"
#include "n1_mutex_linux.c"
#include "n1_fence_linux.c"
#endif

