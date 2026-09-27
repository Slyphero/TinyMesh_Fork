#include "sdf.h"

double SDFSphere::Value(const Vector& p) const
{
    return Norm(p - m_center);
}