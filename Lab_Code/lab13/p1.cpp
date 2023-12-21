#include "stack.h"
#include <iostream>

int main() {
    Stack stack1(5);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack stack2 = stack1; // Copy constructor
    Stack stack3;
    stack3 = stack1; // Assignment operator

    Item popped_item;
    std::cout << "stack2: ";
    while (stack2.pop(popped_item)) {
        std::cout << popped_item << " ";
    }
    std::cout << std::endl;

    std::cout << "stack3: ";
    while (stack3.pop(popped_item)) {
        std::cout << popped_item << " ";
    }
    std::cout << std::endl;

    return 0;
}
