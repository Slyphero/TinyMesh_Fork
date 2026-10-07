#include "blob.h"

double BlobSphere::Value(const Vector& p) const
{
    double squaredDistance = SquaredNorm(p - m_center);
    double ratio = (squaredDistance * m_inverseSquaredRadius);

    if (ratio > 1.0)
        return 0;

    double val = 1 - ratio;
    return val * val;
}


double BlobCapsule::Value(const Vector& p) const
{
    Vector p1p2 = m_p2 - m_p1;
    Vector p2p1 = m_p1 - m_p2;
    Vector p1p = p - m_p1;
    Vector p2p = p - m_p2;

    // p1p2 . p1p: p "before" p1
    if (p1p2 * p1p < 0.0)
    {

    }
    // p2p1 . p2p: p "after" p2
    else if (p2p1 * p2p < 0.0)
    {

    }
    // p between p1 and p2
    else
    {

    }
}
