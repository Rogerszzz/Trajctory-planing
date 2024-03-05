#ifndef FILE_THREE_H
#define FILE_THREE_H

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

} ThreeSegPara;

void ThreeSegPreCal(unsigned int freq, double pos0, double pos1, double velMax, double accMax, ThreeSegPara* threeSegPara);

void ThreeSegHandler(unsigned int count, unsigned int freq, ThreeSegPara* threeSegPara, TrajOut* trajOut);

#endif