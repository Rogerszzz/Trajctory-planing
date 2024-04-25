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

typedef struct
{
    double pos0;
    double pos1;
    double velMax;
    double accMax;
    double jerkMax;
    double snapMax;
} SegmentedTrajectoryPrecalParam;

 
#endif