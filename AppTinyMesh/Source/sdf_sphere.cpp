#include "sdf_sphere.h"

double SDFSphere::Value(const Vector& v) const
{
    return Norm(v - m_center) - m_radius;
}