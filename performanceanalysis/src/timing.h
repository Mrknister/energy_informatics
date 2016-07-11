#ifndef _TIMING_H_
#define _TIMING_H_

#include <sys/types.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>
#include <stdlib.h>
#include <unistd.h>
#if defined(__cplusplus)
extern "C" {
    #endif
    
static int fddev = -1;
__attribute__((constructor)) static void
init(void)
{
 static struct perf_event_attr attr;
 attr.type = PERF_TYPE_HARDWARE;
 attr.config = PERF_COUNT_HW_CPU_CYCLES;
 fddev = syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);
}

__attribute__((destructor)) static void
fini(void)
{
 close(fddev);
}

static inline long long
cpucycles(void)
{
 long long result = 0;
 if (read(fddev, &result, sizeof(result)) < sizeof(result)) return 0;
 return result;
}
    #if defined(__cplusplus)
} /* extern "C" */
#endif

#endif