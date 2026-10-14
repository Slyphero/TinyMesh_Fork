#ifndef IMPLICITBLOB_H
#define IMPLICITBLOB_H

#include <memory>
#include <vector>

#include "ImplicitNode.h"
#include "color.h"

class Potential  // Purement virtuelle
{
 public:
  virtual double Value(const Vector& p) const = 0;
  virtual bool Inside(const Vector& p) const = 0;
  virtual ~Potential() = default;

  void SetColor(const Color& c) { m_color = c; }
  const Color& GetColor() const { return m_color; }

 protected:
  Color m_color = Color(0.5, 0.5, 0.5);
};

class PotentialSphere : public Potential {
 public:
  PotentialSphere(double radius, const Vector& center)
      : m_radius(radius),
        m_center(center),
        m_inverseSquaredRadius(1.0 / (m_radius * m_radius)) {}

  double Value(const Vector& p) const override;
  bool Inside(const Vector& p) const override;

 private:
  double m_radius;
  Vector m_center;
  double m_inverseSquaredRadius;
};

class PotentialCapsule : public Potential {
 public:
  PotentialCapsule(double radius, const Vector& p1, const Vector& p2)
      : m_radius(radius),
        m_p1(p1),
        m_p2(p2),
        m_inverseSquaredRadius(1.0 / (radius * radius)) {}

  double Value(const Vector& p) const override;
  bool Inside(const Vector& p) const override;

 private:
  double m_radius;
  Vector m_p1;
  Vector m_p2;
  double m_inverseSquaredRadius;
};

class ImplicitBlob : public ImplicitNode {
 public:
  ImplicitBlob(double threshold) : m_threshold(threshold) {}

  double Value(const Vector& p) const override;
  void AddPotential(std::shared_ptr<Potential> potential);

  Color ColorAt(const Vector& p) const override;

 private:
  double m_threshold;
  std::vector<std::shared_ptr<Potential>> m_potentials;
};

#endif  // IMPLICITBLOB_H
