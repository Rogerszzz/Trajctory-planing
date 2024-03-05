#include <math.h>
#include "three.h"
#include "common.h"
#include <stdio.h>


void ThreeSegPreCal(unsigned int freq, double pos0, double pos1, double velMax, double accMax, ThreeSegPara* threeSegPara){
    
    double maxVel;
    double accT;
    double constT;
    double decT;
    
    double absDist = fabs(pos1 - pos0);
    unsigned short dir =  (pos1 - pos0) >= 0 ? (1) : (-1);

    maxVel = velMax;
    accT = maxVel / accMax;
    double distOffset = absDist - accT * maxVel;

    threeSegPara->pos0 = pos0;
    threeSegPara->pos1 = pos1;
    threeSegPara->maxAcc = accMax;

    if (distOffset > 0){
        constT = (absDist - accT * maxVel) / maxVel;
        decT = accT;
    } else{
        maxVel = sqrt(absDist * accMax);
        accT = maxVel / accMax;
        decT = accT;
        constT = 0;
    }
    threeSegPara->accT = accT;
    threeSegPara->constT = constT;
    threeSegPara->decT = decT;
    threeSegPara->maxVel = maxVel;

    threeSegPara->accTSamples = (unsigned int)(accT * freq + 0.5);
    threeSegPara->constTSamples = (unsigned int)(constT * freq + 0.5);
    threeSegPara->decTSamples = (unsigned int)(decT * freq + 0.5);

    threeSegPara->totalSamples = threeSegPara->accTSamples + threeSegPara->constTSamples + threeSegPara->decTSamples;

    threeSegPara->accT = threeSegPara->accTSamples / freq;
    threeSegPara->constT = threeSegPara->constTSamples / freq;
    threeSegPara->decT = threeSegPara->decTSamples / freq;
    threeSegPara->maxVel = threeSegPara->accT * accMax;

    return;
}

void ThreeSegHandler(unsigned int count, unsigned int freq, ThreeSegPara* threeSegPara, TrajOut* trajOut){
    
    double a, v, p, t;

    if (count > 0 && count <= threeSegPara->accTSamples){
        t = (double)count / freq;
        a = threeSegPara->maxAcc;
        v = threeSegPara->maxAcc * t;
        p = 0.5 * threeSegPara->maxAcc * t * t;
    } else if (count > threeSegPara->accTSamples && count <= threeSegPara->accTSamples + threeSegPara->constTSamples){
        t = (double)count / freq;
        a = 0;
        v = threeSegPara->maxAcc * threeSegPara->accT;
        p = 0.5 * threeSegPara->maxVel * threeSegPara->accT + threeSegPara->maxVel * (t - threeSegPara->accT);
    } else if (count > threeSegPara->accTSamples + threeSegPara->constTSamples && count <= threeSegPara->totalSamples){
        t = (double)count / freq;
        a = -threeSegPara->maxAcc;
        v = threeSegPara->maxVel - threeSegPara->maxAcc * (t - threeSegPara->accT - threeSegPara->constT);
        p = 0.5 * threeSegPara->maxVel * threeSegPara->accT + 
            threeSegPara->maxVel * (t - threeSegPara->accT) - 
            0.5 * threeSegPara->maxAcc * (t - threeSegPara->accT - threeSegPara->constT) * (t - threeSegPara->accT - threeSegPara->constT);
    } else{
        return;
    }

    trajOut->acc = a;
    trajOut->vel = v;
    trajOut->pos = p;
    return;
}
