#include "ImplicitOperators.h"

double ImplicitUnion::Value(const Vector &p) const
{
    return Math::Min(m_left->Value(p), m_right->Value(p));
}

double ImplicitIntersection::Value(const Vector &p) const
{
    return Math::Max(m_left->Value(p), m_right->Value(p));
}

double ImplicitDifference::Value(const Vector &p) const
{
    return Math::Max(m_left->Value(p), -m_right->Value(p));
}

double ImplicitSmoothUnion::Value(const Vector &p) const
{
    double h = Math::Max(m_r - std::abs(m_left->Value(p) - m_right->Value(p)), 0) / m_r;
    double cubicH = h * h * h;
    double offset = (1 / 6) * m_r * cubicH;

    return Math::Min(m_left->Value(p), m_right->Value(p)) - offset;
}