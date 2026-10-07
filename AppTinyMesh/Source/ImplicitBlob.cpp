#include "ImplicitBlob.h"

// Implicit Blob
void ImplicitBlob::AddPotential(std::shared_ptr<Potential> potential) {
  m_potentials.emplace_back(potential);
}

double ImplicitBlob::Value(const Vector &p) const {
  double total = 0.0;

  for (std::shared_ptr<Potential> potential : m_potentials) {
    total += potential->Value(p);
  }

  return m_threshold - total;
}

// Potential Sphere
double PotentialSphere::Value(const Vector &p) const {
  double squaredDistance = SquaredNorm(p - m_center);
  double ratio = (squaredDistance * m_inverseSquaredRadius);

  if (ratio > 1.0) {
    return 0;
  }

  double val = 1 - ratio;
  return val * val;
}

double PotentialCapsule::Value(const Vector &p) const {
  Vector p1p2 = m_p2 - m_p1;
  Vector p2p1 = m_p1 - m_p2;
  Vector p1p = p - m_p1;
  Vector p2p = p - m_p2;

  double squaredDistance;
  double ratio;

  // p1p2 . p1p: p "before" p1
  if (p1p2 * p1p < 0.0) {
    squaredDistance = SquaredNorm(p - m_p1);
  }
  // p2p1 . p2p: p "after" p2
  else if (p2p1 * p2p < 0.0) {
    squaredDistance = SquaredNorm(p - m_p2);
  }
  // p between p1 and p2
  else {
    double dp = p1p2 * p1p;
    double len = p1p2 * p1p2;
    squaredDistance = (p1p * p1p) - (dp * dp) / (len + 0.000001);
  }

  ratio = (squaredDistance * m_inverseSquaredRadius);
  if (ratio > 1.0)
    return 0;

  return (1 - ratio) * (1 - ratio);
}
