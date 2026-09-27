#ifndef SDF_H
#define SDF_H

#include "mathematics.h"

class SDF
{
public:
    virtual double Value(const Vector&) const = 0;
protected:
};

class SDFSphere : public SDF
{
public:
    SDFSphere(double radius, const Vector& center) :
        m_radius(radius),
        m_center(center) {}

    double Value(const Vector& p) const override;
private:
    double m_radius;
    Vector m_center;
};

#endif // SDF_H
