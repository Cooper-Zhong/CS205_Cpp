#include "p2.h"
#include "iostream"
int main() {
    int n;
    std::cout << "Enter the number of sales: ";
    std::cin >> n;

    double salesData[n];
    std::cout << "Enter the sales data: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> salesData[i];
    }
    SALES::Sales mySales;
//    double salesData[SALES::QUARTERS] = {1200.5, 2300.0, 1800.75, 2500.25};
    SALES::setSales(mySales, salesData, n);
    SALES::showSales(mySales, n);



    return 0;
}
