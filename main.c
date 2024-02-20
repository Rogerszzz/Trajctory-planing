#include <stdio.h>
#include "fifteen.h"
#include "three.h"

void main(){
    // ThreeSegPara* threeSegPara = (ThreeSegPara*)malloc(sizeof(ThreeSegPara));
    ThreeSegPara threeSegPara;  
    ThreeSegPreCal(0, 0.02, 0.01, 0.01, &threeSegPara);
    printf("%f",threeSegPara.maxVel);
}