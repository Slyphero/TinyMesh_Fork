#ifndef IMPLICIT_SPHERE_H
#define IMPLICIT_SPHERE_H

#include "implicits.h"

class ImplicitSphere : public AnalyticScalarField
{
public:
    ImplicitSphere() : m_radius(1.0), m_center(Vector(0.0, 0.0, 0.0)) {}
    ImplicitSphere(double radius, const Vector& center) : m_radius(radius), m_center(center) {}
    double Value(const Vector& v) const;
protected:
    double m_radius;
    Vector m_center;
};

#endif // IMPLICIT_SPHERE_H
