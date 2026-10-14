#ifndef SDF_H
#define SDF_H

#include "ImplicitNode.h"
#include "mathematics.h"

class SDFPrimitive : public ImplicitNode {
 public:
  void SetColor(const Color& c) { m_color = c; }
  const Color& GetColor() const { return m_color; }
  Color ColorAt(const Vector& p) const override { return m_color; }

 protected:
  Color m_color = Color(0.5, 0.5, 0.5);
};

class SDFSphere : public SDFPrimitive {
 public:
  SDFSphere(double radius, const Vector& center)
      : m_radius(radius), m_center(center) {}

  double Value(const Vector& p) const override;

 private:
  double m_radius;
  Vector m_center;
};

class SDFCapsule : public SDFPrimitive {
 public:
  SDFCapsule(double radius, const Vector& p1, const Vector& p2)
      : m_radius(radius), m_p1(p1), m_p2(p2) {}

  double Value(const Vector& p) const override;

 private:
  double m_radius;
  Vector m_p1;
  Vector m_p2;
};

class SDFTorus : public SDFPrimitive {
 public:
  SDFTorus(double ringSize, double thickness, const Vector& center)
      : m_ringSize(ringSize), m_thickness(thickness), m_center(center) {}

  double Value(const Vector& p) const override;

 private:
  double m_ringSize;
  double m_thickness;
  Vector m_center;
};

class SDFEllipsoid : public SDFPrimitive {
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

class SDFBox : public SDFPrimitive {
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
