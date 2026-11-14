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

double SDFEllipsoid::Value(const Vector &p) const
{
    double first = ( (m_center[0] - p[0]) * (m_center[0] - p[0]) ) / (m_xSize * m_xSize);
    double second = ( (m_center[1] - p[1]) * (m_center[1] - p[1]) )/ (m_ySize * m_ySize);
    double third = ( (m_center[2] - p[2]) * (m_center[2] - p[2]) ) / (m_zSize * m_zSize);

    return first + second + third - 1;
}

double SDFBox::Value(const Vector &p) const
{
    Vector q = p - m_center;
    double dx = std::abs(q[0]) - m_x;
    double dy = std::abs(q[1]) - m_y;
    double dz = std::abs(q[2]) - m_z;

    Vector outside(Math::Max(dx, 0.0), Math::Max(dy, 0.0), Math::Max(dz, 0.0));

    return Norm(outside) + Math::Min(Math::Max(dx, Math::Max(dy, dz)), 0.0);
}

double SDFPlane::Value(const Vector &p) const
{
    return m_n * p + m_h;
}

double SDFCylinder::Value(const Vector &p) const
{
    auto capsule = std::make_shared<SDFCapsule>(m_radius, m_p1, m_p2);
    Vector n = Normalized(m_p2 - m_p1);

    auto plane1 = std::make_shared<SDFPlane>(-n, m_p1 * n);
    auto plane2 = std::make_shared<SDFPlane>(n, -(m_p2 * n));

    return Math::Max(capsule->Value(p), Math::Max(plane1->Value(p), plane2->Value(p)));
}

double SDFCone::Value(const Vector &p) const
{
    Vector q = p - m_center;
    Vector q_xz(q[0], q[2], 0.0);

    Vector v(Norm(q_xz), q[1], 0.0);
    return Math::Max( v[0] * std::cos(m_halfAngleRad) - v[1] * std::sin(m_halfAngleRad), v[1] - m_height );
}
