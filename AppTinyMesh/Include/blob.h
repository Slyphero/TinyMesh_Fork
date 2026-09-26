#ifndef BLOB_H
#define BLOB_H

#include "memory"

#include "implicits.h"
#include "sdf.h"

class Blob : public AnalyticScalarField
{
public:
    Blob() = delete;
    Blob(const std::unique_ptr<SDF>& toSmoothSDF);
    double Value(const Vector& v) const;
private:
    std::unique_ptr<SDF> m_toSmoothValue;
};

#endif // BLOB_H