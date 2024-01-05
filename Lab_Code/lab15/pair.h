#include <iostream>
#include <string>
using namespace std;

template <class T1, class T2>
class Pair
{
public:
    T1 key;
    T2 value;
    Pair(T1 k, T2 v) : key(k), value(v) {}
    bool operator<(const Pair<T1, T2> &p) const
    {
        return key < p.key;
    }
    friend ostream &operator<<(ostream &os, const Pair<T1, T2> &p)
    {
        os << p.key << " " << p.value;
        return os;
    }
};