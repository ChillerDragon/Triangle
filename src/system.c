#include "detect.h"

#ifdef OS_WINDOWS
#include <windows.h>
#endif

#ifdef OS_UNIX
#include <sys/time.h>
#include <time.h>
#endif

#include "system.h"

long long time_get() {
#ifdef WIN32
  static int64 last = 0;
  int64 t;
  QueryPerformanceCounter((PLARGE_INTEGER)&t);
  if (t < last) /* for some reason, QPC can return values in the past */
    return last;
  last = t;
  return t;
#else
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (long long)tv.tv_sec * (long long)1000000 + (long long)tv.tv_usec;
#endif
}

long long time_freq() {
#ifdef WIN32
  int64 t;
  QueryPerformanceFrequency((PLARGE_INTEGER)&t);
  return t;

#else
  return 1000000;
#endif
}
