#include <math.h>
#include "three.h"
#include "common.h"
#include <stdio.h>


void ThreeSegPreCal(double pos0, double pos1, double velMax, double accMax, ThreeSegPara* threeSegPara){
    
    printf("1");
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
}

//void ThreeSegHandler(unsigned int count, ThreeSegPara threeSegPara, TrajOut trajOut);