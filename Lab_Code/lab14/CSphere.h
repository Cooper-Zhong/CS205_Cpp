#ifndef CSPHERE_H
#define CSPHERE_H

#include "CStereoShape.h"

class CSphere : public CStereoShape {
private:
    double radius;

public:
    CSphere(double r);

    double GetArea() override;
    double GetVolume() override;
    void Show() override;
};

#endif // CSPHERE_H
