#ifndef IMPLICITOPERATORS_H
#define IMPLICITOPERATORS_H

#include "ImplicitNode.h"
#include "mathematics.h"

class ImplicitBinaryOperator : public ImplicitNode
{
  public:
    ImplicitBinaryOperator(std::shared_ptr<ImplicitNode> left, std::shared_ptr<ImplicitNode> right)
        : m_left(left), m_right(right)
    {
    }

  protected:
    std::shared_ptr<ImplicitNode> m_left;
    std::shared_ptr<ImplicitNode> m_right;
};

class ImplicitUnion : public ImplicitBinaryOperator
{
  public:
    using ImplicitBinaryOperator::ImplicitBinaryOperator;
    double Value(const Vector &p) const override;
};

class ImplicitIntersection : public ImplicitBinaryOperator
{
  public:
    using ImplicitBinaryOperator::ImplicitBinaryOperator;
    double Value(const Vector &p) const override;
};

class ImplicitDifference : public ImplicitBinaryOperator
{
  public:
    using ImplicitBinaryOperator::ImplicitBinaryOperator;
    double Value(const Vector &p) const override;
};

class ImplicitSmoothUnion : public ImplicitBinaryOperator 
{
  public:
    ImplicitSmoothUnion(std::shared_ptr<ImplicitNode> left, std::shared_ptr<ImplicitNode> right,
                        double r)
        : ImplicitBinaryOperator(std::move(left), std::move(right)), m_r(r)
    {
    }
    double Value(const Vector &p) const override;

  protected:
    double m_r;
};
#endif // IMPLICITOPERATORS_H
