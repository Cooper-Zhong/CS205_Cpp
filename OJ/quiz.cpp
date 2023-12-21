#include <iostream>

// void print(const char* str, int times);
struct vector
{
    int x;
    int y;

};

inline int func(int n){
    if (n==1) return 1;
    else return n*func(n-1);
}

template <typename T>
T larger(T a, T b){
    return a>b?a:b;
}

int main(){
    // print("hello");
    // vector a = {1,2};
    // vector b = {3,-4};
    // std::cout<< larger(1,2) << larger(a,b).x << std::endl;
    std::cout << func(3) << std::endl;
    return 0;
}

// void print(const char* str, int times=2){
//     for(int i=0; i<times; i++){
//         std::cout << str << std::endl;
//     }
// }