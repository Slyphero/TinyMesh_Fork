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
    Color ColorAt(const Vector &p) const override;
};

class ImplicitIntersection : public ImplicitBinaryOperator
{
  public:
    using ImplicitBinaryOperator::ImplicitBinaryOperator;
    double Value(const Vector &p) const override;
    Color ColorAt(const Vector &p) const override;
};

class ImplicitDifference : public ImplicitBinaryOperator
{
  public:
    using ImplicitBinaryOperator::ImplicitBinaryOperator;
    double Value(const Vector &p) const override;
    Color ColorAt(const Vector &p) const override;
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
    Color ColorAt(const Vector &p) const override;

  protected:
    double m_r;
};

class ImplicitUnaryOperator : public ImplicitNode
{
  public:
    ImplicitUnaryOperator(std::shared_ptr<ImplicitNode> node) : m_node(node)
    {
    }
  protected:
    std::shared_ptr<ImplicitNode> m_node;
};

class ImplicitTranslation : public ImplicitUnaryOperator
{
  public:
    ImplicitTranslation(std::shared_ptr<ImplicitNode> node, Vector t) :
        ImplicitUnaryOperator(std::move(node)), m_t(t)
    {
    }
    double Value(const Vector &p) const override;
    Color ColorAt(const Vector &p) const override;
  protected:
    Vector m_t;
};

class ImplicitScale : public ImplicitUnaryOperator
{
  public:
    ImplicitScale(std::shared_ptr<ImplicitNode> node, double lambda) :
        ImplicitUnaryOperator(std::move(node)), m_lambda(lambda)
    {
    }
    double Value(const Vector &p) const override;
    Color ColorAt(const Vector &p) const override;
  protected:
    double m_lambda;
};

#endif // IMPLICITOPERATORS_H
