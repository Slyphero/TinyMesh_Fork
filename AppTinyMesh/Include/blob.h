#ifndef BLOB_H
#define BLOB_H

#include "mathematics.h"

class Blob
{
public:
    virtual double Value(const Vector&) const = 0;

protected:

};

class BlobSphere : public Blob
{
public:
    BlobSphere(double radius, const Vector& center) :
        m_radius(radius),
        m_center(center),
        m_inverseSquaredRadius(1.0 / m_radius * m_radius) {}

    double Value(const Vector& p) const override;
private:
    double m_radius;
    Vector m_center;
    double m_inverseSquaredRadius;
};

class BlobCapsule : public Blob
{
public:
    BlobCapsule(double radius, const Vector& p1, const Vector& p2) :
        m_radius(radius),
        m_p1(p1),
        m_p2(p2) {}

    double Value(const Vector& p) const override;
private:
    double m_radius;
    Vector m_p1;
    Vector m_p2;
};


#endif // BLOB_H
