#include <sys/time.h>
#include <time.h>

#include "system.h"

long long time_get() {
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (long long)tv.tv_sec * (long long)1000000 + (long long)tv.tv_usec;
}

long long time_freq() { return 1000000; }
