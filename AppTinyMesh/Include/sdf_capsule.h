#ifndef SDF_CAPSULE_H
#define SDF_CAPSULE_H

#include "sdf.h"

class SDFCapsule : public SDF
{
public:
    SDFCapsule() = delete;
    SDFCapsule(double radius, const Vector& a, const Vector& b) :
        m_radius(radius), m_a(a), m_b(b) {}

    double Value(const Vector& v) const;
    ~SDFCapsule() = default;
private:
    double m_radius;
    Vector m_a;
    Vector m_b;
};


#endif // SDF_CAPSULE_H

