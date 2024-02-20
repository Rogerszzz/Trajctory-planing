#ifndef FILE_COMMON_H
#define FILE_COMMON_H

typedef struct 
{
    double pos;
    double vel;
    double acc;
    double jerk;
    double snap;
} TrajOut;

int add(int a, int b);
 
#endif