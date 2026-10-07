#ifndef SDF_H
#define SDF_H

#include "mathematics.h"
#include "ImplicitNode.h"

class SDF
{
public:
    virtual double Value(const Vector&) const = 0;
protected:
};

class SDFSphere : public ImplicitNode
{
public:
    SDFSphere(double radius, const Vector& center) :
        m_radius(radius),
        m_center(center) {}

    double Value(const Vector& p) const override;
private:
    double m_radius;
    Vector m_center;
};

class SDFCapsule : public ImplicitNode
{
public:
    SDFCapsule(double radius, const Vector& p1, const Vector& p2) :
        m_radius(radius),
        m_p1(p1),
        m_p2(p2) {}

    double Value(const Vector& p) const override;
private:
    double m_radius;
    Vector m_p1;
    Vector m_p2;
};

#endif // SDF_H
