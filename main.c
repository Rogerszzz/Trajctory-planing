#include <stdio.h>
#include "common.h"
#include "SegmentedTrajectory.h"

void main(){
    // ThreeSegPara* threeSegPara = (ThreeSegPara*)malloc(sizeof(ThreeSegPara));
    SegmentedTrajectoryPrecalParam trapeziodInput;
    trapeziodInput.pos0 = 0;
    trapeziodInput.pos1 = 0.03;
    trapeziodInput.velMax = 0.01;
    trapeziodInput.accMax = 0.02;

    TrapeziodPara trapeziodPara;
    TrajOut trajOut;
    FILE* fp;
    fp = fopen("res.csv", "w");
    char line[1024];
    unsigned int freq = 10000;
    TrapeziodPreCal(freq, &trapeziodInput, &trapeziodPara);
    for (int count = 1; count <= trapeziodPara.totalSamples; count++){
        TrapeziodHandler(count, freq, &trapeziodPara, &trajOut);
        sprintf(line, "%d, %.12f, %.12f, %.12f\n", count, trajOut.acc, trajOut.vel, trajOut.pos);
        fprintf(fp, "%s", line);
    }
    return;
}