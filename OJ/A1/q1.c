//
// Created by 志源 on 2023/10/9.
//

#include <stdio.h>
#include <math.h>

#define pi 3.1415926

float toDegrees(float radians) {
    return radians * 180 / pi;
}

float toRadians(float degrees) {
    return degrees * pi / 180;
}

int main() {
    float angle, ans;
    char type;
    scanf("%f", &angle);
    scanf(" %c", &type);
    if (type == 'd') {
        ans = toRadians(angle);
        printf("%.2f", ans);
    } else if (type == 'r') {
        ans = toDegrees(angle);
        printf("%.2f", ans);
    }
    return 0;
}