#ifndef IMPLICITBLOB_H
#define IMPLICITBLOB_H

#include <memory>
#include <vector>

#include "ImplicitNode.h"

class Potential // Purement virtuelle
{
public:
    virtual double Value(const Vector& p) const = 0;
};

class PotentialSphere : public Potential
{
public:
    PotentialSphere(double radius, const Vector& center):
        m_radius(radius),
        m_center(center),
        m_inverseSquaredRadius(1.0 / (m_radius * m_radius)) {}

    double Value(const Vector& p) const;
private:
    double m_radius;
    Vector m_center;
    double m_inverseSquaredRadius;
};

class PotentialCapsule : public Potential
{
public:
    PotentialCapsule(double radius, const Vector& p1, const Vector& p2) :
        m_radius(radius),
        m_p1(p1),
        m_p2(p2) {}

    double Value(const Vector& p) const;
private:
    double m_radius;
    Vector m_p1;
    Vector m_p2;
};

class ImplicitBlob : public ImplicitNode
{
public:
    double Value(const Vector& p) const;
    void AddPotential(std::shared_ptr<Potential> potential);
private:
    double m_threshold = 0.1;
    std::vector<std::shared_ptr<Potential>> m_potentials;
};

#endif // IMPLICITBLOB_H
