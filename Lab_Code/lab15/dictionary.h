#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

template <class Key, class Value>
class Dictionary
{
    Key *keys;
    Value *values;
    int size;
    int max_size;

public:
    Dictionary(int initial_size) : size(0)
    {
        max_size = 1;
        while (initial_size >= max_size)
            max_size *= 2;
        keys = new Key[max_size];
        values = new Value[max_size];
    }
    void add(Key key, Value value)
    {
        Key *tmpKey;
        Value *tmpVal;
        if (size + 1 >= max_size)
        {
            max_size *= 2;
            tmpKey = new Key[max_size];
            tmpVal = new Value[max_size];
            for (int i = 0; i < size; i++)
            {
                tmpKey[i] = keys[i];
                tmpVal[i] = values[i];
            }
            tmpKey[size] = key;
            tmpVal[size] = value;
            delete[] keys;
            delete[] values;
            keys = tmpKey;
            values = tmpVal;
        }
        else
        {
            keys[size] = key;
            values[size] = value;
        }
        size++;
    }
    void print()
    {
        for (int i = 0; i < size; i++)
            cout << "{" << keys[i] << ", " << values[i] << "}" << endl;
    }
    ~Dictionary()
    {
        delete[] keys;
        delete[] values;
    }
};

namespace specialization
{

    template <class Value>
    class Dictionary<int, Value> // Partial specialization for Key as int
    {
        int *keys;
        Value *values;
        int size;
        int max_size;

    public:
        Dictionary(int initial_size) : size(0)
        {
            max_size = 1;
            while (initial_size >= max_size)
                max_size *= 2;
            keys = new int[max_size];
            values = new Value[max_size];
        }

        void add(int key, Value value)
        {
            // The add function remains unchanged
            // ...
            int *tmpKey;
            Value *tmpVal;
            if (size + 1 >= max_size)
            {
                max_size *= 2;
                tmpKey = new int[max_size];
                tmpVal = new Value[max_size];
                for (int i = 0; i < size; i++)
                {
                    tmpKey[i] = keys[i];
                    tmpVal[i] = values[i];
                }
                tmpKey[size] = key;
                tmpVal[size] = value;
                delete[] keys;
                delete[] values;
                keys = tmpKey;
                values = tmpVal;
            }
            else
            {
                keys[size] = key;
                values[size] = value;
            }
            size++;

            // No changes here
        }

        void print()
        {
            Dictionary<int, Value>::print();
        }

        void sort()
        {
            // Use std::sort to sort keys and values simultaneously based on keys
            std::pair<int, Value> *sortedArray = new std::pair<int, Value>[size];

            for (int i = 0; i < size; ++i)
            {
                sortedArray[i] = std::make_pair(keys[i], values[i]);
            }

            std::sort(sortedArray, sortedArray + size);

            for (int i = 0; i < size; ++i)
            {
                keys[i] = sortedArray[i].first;
                values[i] = sortedArray[i].second;
            }

            delete[] sortedArray;
        }

        ~Dictionary()
        {
            delete[] keys;
            delete[] values;
        }
    };
}