#include <iostream>
#include <iomanip>

#include "CCube.h"
#include "CSphere.h"
#include "CStereoShape.h"
int CStereoShape::numberOfObject = 0;

int main()
{
    
    CCube a_cube(4.0, 5.0, 6.0);
    CSphere c_sphere(7.9);

    CStereoShape *p;

    p = &a_cube;
    p->Show();

    p = &c_sphere;
    p->Show();

    std::cout << "Number of objects: " << CStereoShape::GetNumOfObject() << std::endl;

    return 0;
}
