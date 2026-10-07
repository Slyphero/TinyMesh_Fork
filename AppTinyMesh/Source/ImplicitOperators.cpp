#include "ImplicitOperators.h"

double ImplicitUnion::Value(const Vector& p) const
{
    return Math::Min(m_left->Value(p), m_right->Value(p));
}

double ImplicitIntersection::Value(const Vector& p) const
{
    return Math::Max(m_left->Value(p), m_right->Value(p));
}

double ImplicitDifference::Value(const Vector& p) const
{
    return Math::Max(m_left->Value(p), -m_right->Value(p));
}
