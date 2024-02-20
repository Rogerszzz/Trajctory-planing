#ifndef FILE_FIFTEEN_H
#define FILE_FIFTEEN_H

#include "common.h"

typedef struct
{
    
} FifteenSegPara;

void FifteenSegPreCal(double pos1, double pos2, double velMax, double accMax, double jerkMax, double snapMax, FifteenSegPara* fifteenSegPara);

void FifteenSegHandler(unsigned int count, FifteenSegPara fifteenSegPara, TrajOut* trajOut);

#endif