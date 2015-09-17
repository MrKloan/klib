#ifndef KLIB_TIMER_H
#define	KLIB_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef WIN32
    #define EPOCH 116444736000000000ULL
    int gettimeofday(struct timeval*, struct timeval*);
#endif
    
enum {
    TIMER_START,
    TIMER_STOP
};

typedef struct Timer {
    struct timeval _time[2];
    clock_t _cpu[2];
    
    boolean (*start)(struct Timer*);
    boolean (*stop)(struct Timer*);
    double (*time)(struct Timer*);
    int (*cpu)(struct Timer*);
    double (*cpuTime)(struct Timer*);
    
    void (*free)(struct Timer*);
} Timer;

Timer* libexp TimerNew(void);
void libexp TimerInit(Timer*);
void libexp TimerFree(Timer*);

boolean libexp TimerStart(Timer*);
boolean libexp TimerStop(Timer*);
double libexp TimerTime(Timer*);
int libexp TimerCPU(Timer*);
double libexp TimerCPUTime(Timer*);

#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_TIMER_H */

