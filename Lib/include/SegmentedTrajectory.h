#ifndef FILE_SEGMENTEDTRAJECTORY_H
#define FILE_SEGMENTEDTRAJECTORY_H

#include "common.h"

typedef struct
{   
    double pos0;
    double pos1;
    double maxAcc;
    double maxVel;

    double accT;
    double constT;
    double decT;

    unsigned int accTSamples;
    unsigned int constTSamples;
    unsigned int decTSamples;
    unsigned int totalSamples;  

} TrapeziodPara;

typedef struct
{   
    double pos0;
    double pos1;
    double maxAcc;
    double maxVel;
    double maxJerk;

    double jerkaccT;
    double accT;
    double accConstT;
    double constT;
    double decT;

    unsigned int accTSamples;
    unsigned int constTSamples;
    unsigned int decTSamples;
    unsigned int totalSamples;  

} SevenSegPara;

typedef struct
{
    
} FifteenSegPara;

void TrapeziodPreCal(unsigned int freq, double pos0, double pos1, double velMax, double accMax, TrapeziodPara* trapeziodPara);

void TrapeziodHandler(unsigned int count, unsigned int freq, TrapeziodPara* trapeziodPara, TrajOut* trajOut);

void SevenSegPreCal(unsigned int freq, double pos0, double pos1, double velMax, double accMax, SevenSegPara* threeSegPara);

void SevenSegHandler(unsigned int count, unsigned int freq, SevenSegPara* threeSegPara, TrajOut* trajOut);

void FifteenSegPreCal(double pos1, double pos2, double velMax, double accMax, double jerkMax, double snapMax, FifteenSegPara* fifteenSegPara);

void FifteenSegHandler(unsigned int count, FifteenSegPara fifteenSegPara, TrajOut* trajOut);
#endif