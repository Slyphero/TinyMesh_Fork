#include "blob.h"

double BlobSphere::Value(const Vector& p) const
{
    double squaredDistance = SquaredNorm(p - m_center);
    double ratio = (squaredDistance * m_inverseSquaredRadius);

    if (ratio > 1.0) return 0;

    double val = 1 - ratio;
    return val * val;
}