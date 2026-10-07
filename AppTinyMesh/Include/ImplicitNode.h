#ifndef IMPLICITNODE_H
#define IMPLICITNODE_H

#include "mathematics.h"

#include <memory>

class ImplicitNode // Purement virtuelle
{
public:
  virtual double Value(const Vector &p) const = 0;
  virtual ~ImplicitNode() = default;

protected:
};

#endif // IMPLICITNODE_H
