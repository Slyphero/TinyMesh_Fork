#include "sdf.h"

double SDFSphere::Value(const Vector &p) const
{
    return Norm(p - m_center) - m_radius;
}

double SDFCapsule::Value(const Vector &p) const
{
    Vector p1p2 = m_p2 - m_p1;
    Vector p1p = p - m_p1;

    double t = (p1p * p1p2) / (p1p2 * p1p2 + 1e-9);
    t = Math::Clamp(t, 0.0, 1.0);

    return Norm(p1p - t * p1p2) - m_radius;
}

double SDFTorus::Value(const Vector &p) const
{
    Vector q = p - m_center;
    double dxy = sqrt(q[0] * q[0] + q[1] * q[1]) - m_ringSize;
    return sqrt(dxy * dxy + q[2] * q[2]) - m_thickness;
}
