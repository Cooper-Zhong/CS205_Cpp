#ifndef CCUBE_H
#define CCUBE_H

#include "CStereoShape.h"

class CCube : public CStereoShape {
private:
    double length, width, height;

public:
    CCube(double l, double w, double h);

    double GetArea() override;
    double GetVolume() override;
    void Show() override;
};

#endif // CCUBE_H
