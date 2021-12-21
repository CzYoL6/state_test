#ifndef UTIL_H
#define UTIL_H

#include<cmath>

#define RAD2DEG  (45.0 / atan(1.0))

float TwoPoint2Degree(float x1, float y1, float x2, float y2){
    float diff_x = x2 - x1;
    float diff_y = y2 - y1;
    float rotation = atan2(diff_x, -diff_y) * RAD2DEG;
    // printf("%lf\n", RAD2DEG);
    return rotation;
}

#endif