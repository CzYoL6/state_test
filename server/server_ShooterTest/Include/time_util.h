#pragma once
#include "ikcp.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <chrono>

class Timer{
public:
    Timer(){
        Reset();
    }
    void Reset(){
        start = end = std::chrono::system_clock::now();
    }
    const double GetElapsedTime(){
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        return elapsed.count();
    }
    ~Timer(){}
private:
    std::chrono::system_clock::time_point start, end;
};


/* get system time */
static inline void itimeofday(long *sec, long *usec) {
    struct timeval time;
    gettimeofday(&time, NULL);
    if (sec)
        *sec = time.tv_sec;
    if (usec)
        *usec = time.tv_usec;
}

/* get clock in millisecond 64 */
static inline IINT64 iclock64(void) {
    long s, u;
    IINT64 value;
    itimeofday(&s, &u);
    value = ((IINT64)s) * 1000 + (u / 1000);
    return value;
}

static inline IUINT32 iclock() {
    return (IUINT32)(iclock64() & 0xfffffffful);
}

/* sleep in millisecond */
static inline void isleep(unsigned long millisecond) {
#ifdef __unix /* usleep( time * 1000 ); */
    struct timespec ts;
    ts.tv_sec = (time_t)(millisecond / 1000);
    ts.tv_nsec = (long)((millisecond % 1000) * 1000000);
    /*nanosleep(&ts, NULL);*/
    usleep((millisecond << 10) - (millisecond << 4) - (millisecond << 3));
#elif defined(_WIN32)
    Sleep(millisecond);
#endif
}