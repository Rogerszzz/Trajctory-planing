#include <stdio.h>
#include "common.h"
#include "SegmentedTrajectory.h"

void main(){
    // ThreeSegPara* threeSegPara = (ThreeSegPara*)malloc(sizeof(ThreeSegPara));
    TrapeziodPara trapeziodPara;
    TrajOut trajOut;
    FILE* fp;
    fp = fopen("res.csv", "w");
    char line[1024];
    unsigned int freq = 10000;
    TrapeziodPreCal(freq, 0, 0.03, 0.01, 0.01, &trapeziodPara);
    for (int count = 1; count <= trapeziodPara.totalSamples; count++){
        TrapeziodHandler(count, freq, &trapeziodPara, &trajOut);
        sprintf(line, "%d, %.12f, %.12f, %.12f\n", count, trajOut.acc, trajOut.vel, trajOut.pos);
        fprintf(fp, "%s", line);
    }
    return;
}