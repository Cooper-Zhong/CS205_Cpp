// div.cpp
float division(int a, int b) {
    if (b != 0) {
        return static_cast<float>(a) / b;
    } else {
        return -1; // Error: division by zero
    }
}
