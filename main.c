#include <stdio.h>
#include "fifteen.h"
#include "three.h"

void main(){
    // ThreeSegPara* threeSegPara = (ThreeSegPara*)malloc(sizeof(ThreeSegPara));
    ThreeSegPara threeSegPara;
    TrajOut trajOut;
    FILE* fp;
    fp = fopen("res.csv", "w");
    char line[1024];
    unsigned int freq = 10000;
    ThreeSegPreCal(freq, 0, 0.03, 0.01, 0.01, &threeSegPara);
    for (int count = 1; count <= threeSegPara.totalSamples; count++){
        ThreeSegHandler(count, freq, &threeSegPara, &trajOut);
        sprintf(line, "%d, %.12f, %.12f, %.12f\n", count, trajOut.acc, trajOut.vel, trajOut.pos);
        fprintf(fp, "%s", line);
    }
    return;
}