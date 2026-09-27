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
        m_inverseSquaredRadius(1 / m_radius * m_radius) {}

    double Value(const Vector& p) const override;
private:
    double m_radius;
    Vector m_center;
    double m_inverseSquaredRadius;
};

#endif // BLOB_H
