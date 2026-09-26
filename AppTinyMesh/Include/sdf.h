#ifndef SDF_H
#define SDF_H

#include "implicits.h"

class SDF : public AnalyticScalarField
{
public:
    virtual double Value(const Vector&) const = 0;

    virtual ~SDF() = default;
};

#endif // SDF_H
