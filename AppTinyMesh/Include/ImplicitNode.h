#ifndef IMPLICITNODE_H
#define IMPLICITNODE_H

#include <memory>

#include "color.h"
#include "mathematics.h"

class ImplicitNode  // Purement virtuelle
{
 public:
  virtual double Value(const Vector& p) const = 0;
  virtual ~ImplicitNode() = default;
  virtual Color ColorAt(const Vector& p) const = 0;

 protected:
};

#endif  // IMPLICITNODE_H
