//
// Created by 志源 on 2023/10/9.
//

#include <stdio.h>

#define pi 3.1415926535

double getSin(double x, int n) {
    double ans = 0;
    int sign = 1;
    double term = x;
    for (int i = 0; i < n; i++) {
        ans += sign * term;
        sign = -sign;
        term *= x * x / (2 * i + 2) / (2 * i + 3);
    }
    return ans;
}

double getCos(double x, int n) {
    double ans = 0;
    int sign = 1;
    double term = 1;
    for (int i = 0; i < n; i++) {
        ans += sign * term;
        sign = -sign;
        term *= x * x / (2 * i + 1) / (2 * i + 2);
    }
    return ans;
}

int main() {
    double x;
    int n;
    char inType;
    scanf("%lf", &x);
    scanf("%d", &n);
    scanf(" %c", &inType);
    if (inType == 'd') {
        x = x * pi / 180;
    } // convert to radians
    double sin = 0;
    double cos = 0;
    x = x - (int) (x / (2 * pi)) * 2 * pi; // convert to [0, 2pi)
    sin = getSin(x, n);
    cos = getCos(x, n);
    printf("%.2f\n", sin);
    printf("%.2f\n", cos);
}