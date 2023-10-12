//
// Created by 志源 on 2023/10/9.
//

#include <stdio.h>

#define pi 3.141592653589

double getSin(double x, int n) {
    double res = 0.0;
    double term = x;
    int sign = 1;
    for (int i = 1; i <= n; i += 2) {
        res += sign * term;
        sign = -sign;
        term *= (x * x) / ((i + 1) * (i + 2));
    }
    return res;
}

double getCos(double x, int n) {
    double res = 0.0;
    double term = 1.0;
    int sign = 1;
    for (int i = 0; i <= n; i += 2) {
        res += sign * term;
        sign *= -1;
        term *= (x * x) / ((i + 1) * (i + 2));
    }
    return res;
}

int main() {
    double x;
    int n;
    char inType;
    scanf("%lf", &x);
    scanf("%d", &n);
    scanf(" %c", &inType);
    if (inType == 'd') {
        x = x * pi / 180.0;
    } // convert to radians
    x = x - (int) (x / (2 * pi)) * 2 * pi; // convert to [0, 2pi)
    double sin = getSin(x, n);
    double cos = getCos(x, n);
    printf("%.2lf\n", sin);
    printf("%.2lf\n", cos);
}