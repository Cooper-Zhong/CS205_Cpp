#include "stack.h"
#include <iostream>

Stack::Stack(int n) // create an empty stack
{
    size = n > 0 && n < MAX ? n : MAX;
    pitems = new Item[size];
    top = 0;
}

Stack::Stack(const Stack & st)
{
    size = st.size;
    pitems = new Item[size];
    for (int i = 0; i < size; i++)
        pitems[i] = st.pitems[i];
    top = st.top;
}

Stack::~Stack()
{
    delete [] pitems;
}

bool Stack::isempty() const
{
    return top == 0;
}

bool Stack::isfull() const
{
    return top == size;
}

bool Stack::push(const Item & item)
{
    if (top < size)
    {
        pitems[top++] = item;
        return true;
    }
    else
        return false;
}

bool Stack::pop(Item & item)
{
    if (top > 0)
    {
        item = pitems[--top];
        return true;
    }
    else
        return false;
}

Stack& Stack::operator=(const Stack & st)
{
    if (this == &st) // self-assignment
        return *this;
    delete [] pitems;
    size = st.size;
    pitems = new Item[size];
    for (int i = 0; i < size; i++)
        pitems[i] = st.pitems[i];
    top = st.top;
    return *this;
}