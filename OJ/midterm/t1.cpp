//
// Created by 志源 on 2023/11/16.
//

#include <iostream>

using namespace std;

bool isPrime(int n);

int main() {
    int n;
    cin >> n;
    int cnt = 0;
    cout << "prime: ";
    for (int i = 2; i <= n; ++i) {
        if (isPrime(i)) {
            printf("%d ", i);
            cnt++;
        }
    }
    cout << endl;
    printf("count: %d", cnt);
}

bool isPrime(int n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false; //even
    for (int i = 3; i <= n - 1; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}


