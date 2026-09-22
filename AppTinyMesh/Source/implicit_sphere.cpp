#include "implicit_sphere.h"

double ImplicitSphere::Value(const Vector& v) const
{
    double squaredRadius = m_radius * m_radius;
    double squaredDistance = (Norm(v - m_center) * Norm(v - m_center));
    double f = std::min(squaredDistance / squaredRadius, 1.0);
    double g = (1.0 - f);
    return g * g;
}