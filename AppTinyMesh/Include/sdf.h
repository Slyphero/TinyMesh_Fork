#ifndef SDF_H
#define SDF_H

#include "ImplicitNode.h"
#include "mathematics.h"

class SDFSphere : public ImplicitNode {
 public:
  SDFSphere(double radius, const Vector& center)
      : m_radius(radius), m_center(center) {}

  double Value(const Vector& p) const override;

 private:
  double m_radius;
  Vector m_center;
};

class SDFCapsule : public ImplicitNode {
 public:
  SDFCapsule(double radius, const Vector& p1, const Vector& p2)
      : m_radius(radius), m_p1(p1), m_p2(p2) {}

  double Value(const Vector& p) const override;

 private:
  double m_radius;
  Vector m_p1;
  Vector m_p2;
};

class SDFTorus : public ImplicitNode {
 public:
  SDFTorus(double ringSize, double thickness, const Vector& center)
      : m_ringSize(ringSize), m_thickness(thickness), m_center(center) {}

  double Value(const Vector& p) const override;

 private:
  double m_ringSize;
  double m_thickness;
  Vector m_center;
};

class SDFEllipsoid : public ImplicitNode {
 public:
  SDFEllipsoid(double xSize, double ySize, double zSize, const Vector& center)
      : m_xSize(xSize), m_ySize(ySize), m_zSize(zSize), m_center(center) {}

  double Value(const Vector& p) const override;

 private:
  double m_xSize;
  double m_ySize;
  double m_zSize;
  Vector m_center;
};

class SDFBox : public ImplicitNode {
 public:
  SDFBox(double x, double y, double z, const Vector& center)
      : m_x(x), m_y(y), m_z(z), m_center(center) {}
  double Value(const Vector& p) const override;

 private:
  double m_x;
  double m_y;
  double m_z;
  Vector m_center;
};

#endif  // SDF_H
