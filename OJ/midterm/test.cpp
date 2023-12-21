#include <iostream>
#include <cmath>
#include "string"

using namespace std;

int main() {
//    double a, b, c;
//    cin >> a >> b >> c;
//    double p = (a + b + c) / 2;
//    double area = sqrt(p * (p - a) * (p - b) * (p - c));
//    printf("%.1lf", area);

//    int l, m;
//    cin >> l >> m;
//    int *arr = new int[l + 1]();
//    for (int i = 0; i < m; ++i) {
//        int u, v;
//        cin >> u >> v;
//        for (int j = u; j <= v; ++j) {
//            arr[j] = 1;
//        }
//    }
//    int cnt = 0;
//    for (int i = 0; i <= l; ++i) {
//        if (arr[i] == 0) cnt++;
//    }
//    cout << cnt;

    string a, b;
    getline(cin, a);
    getline(cin, b);
    for (int i = 0; i < a.size(); ++i) a[i] = tolower(a[i]);
    for (int i = 0; i < b.size(); ++i) b[i] = tolower(b[i]);
    a=' '+a+' ';
    b=' '+b+' ';

    if (b.find(a) == -1) {
        cout << -1;
        return 0;
    } else {
//        int start = b.find(a);
//        int cnt = 0;
//        int temp = start;
//        while (temp != -1) {
//            temp = b.find(a, temp + 1);
//            cnt++;
//        }

        int alpha=b.find(a);
        int beta=b.find(a),s=0;//计数器初始化为0
        while (beta!=string::npos){
            ++s;//计数器
            beta=b.find(a,beta+1);
        }
        cout<<s<<" "<<alpha<<endl;//输出第一个和总共有几个

//        cout << cnt << " " << start;
    }
}