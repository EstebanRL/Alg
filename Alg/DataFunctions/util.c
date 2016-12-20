#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include "point.h"

int insideCircle(Lpoint *p, Lpoint *c, float radius)
{
    return (p->x - c->x) * (p->x - c->x) + (p->y - c->y) * (p->y - c->y) < radius * radius;
}

// Time
void stclock(struct timespec *start)
{
    clock_gettime(CLOCK_MONOTONIC, start);    
}

void declock(struct timespec *start, struct timespec *end)
{
    double time = 0.0;
    
    clock_gettime(CLOCK_MONOTONIC, end);
    time = ((double)end->tv_sec + 1.0e-9*end->tv_nsec) - ((double)start->tv_sec + 1.0e-9*start->tv_nsec);
    printf("%.2lf s (%.2lf min)\n", time, time / 60.0);
}
void declocksav(struct timespec *start, struct timespec *end, double *time)
{ 
    clock_gettime(CLOCK_MONOTONIC, end);
    *time = ((double)end->tv_sec + 1.0e-9*end->tv_nsec) - ((double)start->tv_sec + 1.0e-9*start->tv_nsec);
}

