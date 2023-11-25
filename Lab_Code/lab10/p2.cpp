#include "p2.h"
#include <iostream>

namespace SALES {
    void setSales(Sales &s, const double ar[], int n) {
        n = (n > QUARTERS) ? QUARTERS : n;

        for (int i = 0; i < n; ++i) {
            s.sales[i] = ar[i];
        }

        double sum = 0.0;
        s.max = ar[0];
        s.min = ar[0];

        for (int i = 0; i < n; ++i) {
            sum += ar[i];
            if (ar[i] > s.max) {
                s.max = ar[i];
            }
            if (ar[i] < s.min) {
                s.min = ar[i];
            }
        }

        s.average = sum / n;
    }

    void showSales(const Sales &s, int n) {
        n = (n > QUARTERS) ? QUARTERS : n;

        std::cout << "Sales array: ";
        for (int i = 0; i < n; ++i) {
            std::cout << s.sales[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Average: " << s.average << std::endl;
        std::cout << "Maximum: " << s.max << std::endl;
        std::cout << "Minimum: " << s.min << std::endl;
    }
}
