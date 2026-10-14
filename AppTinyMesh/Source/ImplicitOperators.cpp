#include "ImplicitOperators.h"

double ImplicitUnion::Value(const Vector& p) const {
  return Math::Min(m_left->Value(p), m_right->Value(p));
}

double ImplicitIntersection::Value(const Vector& p) const {
  return Math::Max(m_left->Value(p), m_right->Value(p));
}

double ImplicitDifference::Value(const Vector& p) const {
  return Math::Max(m_left->Value(p), -m_right->Value(p));
}

double ImplicitSmoothUnion::Value(const Vector& p) const {
  double a = m_left->Value(p);
  double b = m_right->Value(p);
  double h = Math::Max(m_r - std::abs(a - b), 0.0) / m_r;
  double cubicH = h * h * h;
  double offset = (1.0 / 6.0) * m_r * cubicH;

  return Math::Min(a, b) - offset;
}