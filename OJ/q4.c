#include <stdio.h>
#include <math.h>

#define pi 3.1415926535

double max(double a, double b) {
    return a > b ? a : b;
}


int main() {
    int n;
    scanf("%d", &n);
    double arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &arr[i]);
    }
    double ans = -1;
    for (int i = 0; i < (1 << n); ++i) {
        double sum = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                sum += arr[j];
                sum = fmod(sum, 360);
            }
        }
        sum = sum * pi / 180.0;// convert to radians
        sum = sum - (int) (sum / (2 * pi)) * 2 * pi; // convert to [0, 2pi)
        ans = max(ans, sin(sum));
    }
    printf("%.2lf\n", ans);

}