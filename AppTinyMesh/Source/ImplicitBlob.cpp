#include "ImplicitBlob.h"

// Implicit Blob
void ImplicitBlob::AddPotential(std::shared_ptr<Potential> potential)
{
    m_potentials.emplace_back(potential);
}

double ImplicitBlob::Value(const Vector& p) const
{
    double total = 0.0;

    for (std::shared_ptr<Potential> potential : m_potentials)
    {
        total += potential->Value(p);
    }

    return m_threshold - total;
}

// Potential Sphere
double PotentialSphere::Value(const Vector& p) const
{
    double squaredDistance = SquaredNorm(p - m_center);
    double ratio = (squaredDistance * m_inverseSquaredRadius);

    if (ratio > 1.0)
    {
        return 0;
    }

    double val = 1 - ratio;
    return val * val;
}