#ifndef SDF_H
#define SDF_H

#include "ImplicitNode.h"
#include "mathematics.h"

class SDFSphere : public ImplicitNode
{
  public:
    SDFSphere(double radius, const Vector &center) : m_radius(radius), m_center(center)
    {
    }

    double Value(const Vector &p) const override;

  private:
    double m_radius;
    Vector m_center;
};

class SDFCapsule : public ImplicitNode
{
  public:
    SDFCapsule(double radius, const Vector &p1, const Vector &p2)
        : m_radius(radius), m_p1(p1), m_p2(p2)
    {
    }

    double Value(const Vector &p) const override;

  private:
    double m_radius;
    Vector m_p1;
    Vector m_p2;
};

class SDFTorus : public ImplicitNode
{
  public:
    SDFTorus(double ringSize, double thickness, const Vector &center)
        : m_ringSize(ringSize), m_thickness(thickness), m_center(center)
    {
    }

	double Value(const Vector &p) const override;

  private:
    double m_ringSize;
    double m_thickness;
    Vector m_center;
};

#endif // SDF_H
