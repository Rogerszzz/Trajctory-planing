#include <stdio.h>
#include <math.h>

#include "SegmentedTrajectory.h"
#include "common.h"


void TrapeziodPreCal(unsigned int freq, double pos0, double pos1, double velMax, double accMax, TrapeziodPara* trapeziodPara){
    
    double maxVel;
    double accT;
    double constT;
    double decT;
    
    double absDist = fabs(pos1 - pos0);
    unsigned short dir =  (pos1 - pos0) >= 0 ? (1) : (-1);

    maxVel = velMax;
    accT = maxVel / accMax;
    double distOffset = absDist - accT * maxVel;

    trapeziodPara->pos0 = pos0;
    trapeziodPara->pos1 = pos1;
    trapeziodPara->maxAcc = accMax;

    if (distOffset > 0){
        constT = (absDist - accT * maxVel) / maxVel;
        decT = accT;
    } else{
        maxVel = sqrt(absDist * accMax);
        accT = maxVel / accMax;
        decT = accT;
        constT = 0;
    }
    trapeziodPara->accT = accT;
    trapeziodPara->constT = constT;
    trapeziodPara->decT = decT;
    trapeziodPara->maxVel = maxVel;

    trapeziodPara->accTSamples = (unsigned int)(accT * freq + 0.5);
    trapeziodPara->constTSamples = (unsigned int)(constT * freq + 0.5);
    trapeziodPara->decTSamples = (unsigned int)(decT * freq + 0.5);

    trapeziodPara->totalSamples = trapeziodPara->accTSamples + trapeziodPara->constTSamples + trapeziodPara->decTSamples;

    trapeziodPara->accT = trapeziodPara->accTSamples / freq;
    trapeziodPara->constT = trapeziodPara->constTSamples / freq;
    trapeziodPara->decT = trapeziodPara->decTSamples / freq;
    trapeziodPara->maxVel = trapeziodPara->accT * accMax;

    return;
}

void TrapeziodHandler(unsigned int count, unsigned int freq, TrapeziodPara* trapeziodPara, TrajOut* trajOut){
    
    double a, v, p, t;

    if (count > 0 && count <= trapeziodPara->accTSamples){
        t = (double)count / freq;
        a = trapeziodPara->maxAcc;
        v = trapeziodPara->maxAcc * t;
        p = 0.5 * trapeziodPara->maxAcc * t * t;
    } else if (count > trapeziodPara->accTSamples && count <= trapeziodPara->accTSamples + trapeziodPara->constTSamples){
        t = (double)count / freq;
        a = 0;
        v = trapeziodPara->maxAcc * trapeziodPara->accT;
        p = 0.5 * trapeziodPara->maxVel * trapeziodPara->accT + trapeziodPara->maxVel * (t - trapeziodPara->accT);
    } else if (count > trapeziodPara->accTSamples + trapeziodPara->constTSamples && count <= trapeziodPara->totalSamples){
        t = (double)count / freq;
        a = -trapeziodPara->maxAcc;
        v = trapeziodPara->maxVel - trapeziodPara->maxAcc * (t - trapeziodPara->accT - trapeziodPara->constT);
        p = 0.5 * trapeziodPara->maxVel * trapeziodPara->accT + 
            trapeziodPara->maxVel * (t - trapeziodPara->accT) - 
            0.5 * trapeziodPara->maxAcc * (t - trapeziodPara->accT - trapeziodPara->constT) * (t - trapeziodPara->accT - trapeziodPara->constT);
    } else{
        return;
    }

    trajOut->acc = a;
    trajOut->vel = v;
    trajOut->pos = p;
    return;
}
