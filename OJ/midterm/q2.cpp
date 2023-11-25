//
// Created by 志源 on 2023/11/16.
//

#include <iostream>
#include "string"

using namespace std;

bool isBeautiful(string s) {
    int len = s.length();
    if (len % 2 == 1) return false;
//    if (len == 0)return true;
    if (len == 2) {
        return s.substr(0, 1) != s.substr(1, 1);
    }
    string first = s.substr(0, 1);
    string last = s.substr(len - 1, 1);
    if (first == last) return false; //!!!!!!1
//    for (int i = 1; i < len / 2; ++i) {
//        if (s.substr(i, 1) != first || s.substr(len - 1 - i, 1) != last) {
//            return false;
//        }
//    }
    for (int i = 0; i < len / 2 - 1; ++i) {
        if (s.substr(i, 1) != s.substr(i + 1, 1)) return false;
    }
    for (int i = len - 1; i > len / 2; i--) {
        if (s.substr(i, 1) != s.substr(i - 1, 1)) return false;
    }
    return true;
}


int main() {
    char *s;
    string str;

    getline(cin, str);
    int len = str.length();
    int odd = len % 2;
    for (int i = len - odd; i >= 0; i -= 2) { //possible max length from big to small
        for (int j = 0; j + i <= len; ++j) {
            string temp = str.substr(j, i);
            if (isBeautiful(temp)) {
                cout << temp.length();
                return 0;
            }
        }
    }

    return 0;
}

