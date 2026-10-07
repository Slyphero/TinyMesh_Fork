#ifndef IMPLICITOPERATORS_H
#define IMPLICITOPERATORS_H

#include "ImplicitNode.h"
#include "mathematics.h"

class ImplicitUnion : public ImplicitNode
{
public:
    ImplicitUnion(std::shared_ptr<ImplicitNode> left,
       			  std::shared_ptr<ImplicitNode> right) :
        m_left(left),
        m_right(right) {}

    double Value(const Vector& p) const;
protected:
    std::shared_ptr<ImplicitNode> m_left;
    std::shared_ptr<ImplicitNode> m_right;
};

class ImplicitIntersection : public ImplicitNode
{
public:
    ImplicitIntersection(std::shared_ptr<ImplicitNode> left,
                         std::shared_ptr<ImplicitNode> right) :
        m_left(left),
        m_right(right) {}
    double Value(const Vector& p) const;
protected:
    std::shared_ptr<ImplicitNode> m_left;
    std::shared_ptr<ImplicitNode> m_right;
};

class ImplicitDifference : public ImplicitNode
{
public:
    ImplicitDifference(std::shared_ptr<ImplicitNode> left,
    				   std::shared_ptr<ImplicitNode> right) :
        m_left(left),
        m_right(right) {}
    double Value(const Vector& p) const;
protected:
    std::shared_ptr<ImplicitNode> m_left;
    std::shared_ptr<ImplicitNode> m_right;
};

#endif // IMPLICITOPERATORS_H
