#ifndef CSTEREOSHAPE_H
#define CSTEREOSHAPE_H

#include <iostream>

class CStereoShape
{
private:
    static int numberOfObject;

public:
    CStereoShape()
    {
        numberOfObject++;
    }

    virtual double GetArea()
    {
        std::cout << "CStereoShape::GetArea()" << std::endl;
        return 0.0;
    }

    virtual double GetVolume()
    {
        std::cout << "CStereoShape::GetVolume()" << std::endl;
        return 0.0;
    }

    virtual void Show()
    {
        std::cout << "CStereoShape::Show()" << std::endl;
    }

    static int GetNumOfObject()
    {
        return numberOfObject;
    }
};
#endif // CSTEREOSHAPE_H
