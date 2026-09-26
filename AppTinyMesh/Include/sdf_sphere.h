#ifndef SDF_SPHERE_H
#define SDF_SPHERE_H

#include "sdf.h"

class SDFSphere : public SDF
{
public:
    SDFSphere() = delete;
    SDFSphere(const Vector& center, double radius) : m_center(center), m_radius(radius) {}
    double Value(const Vector& v) const;
    ~SDFSphere() = default;
private:
    Vector m_center;
    double m_radius;
};

#endif // SDF_SPHERE_H
