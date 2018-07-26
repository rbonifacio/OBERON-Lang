#ifndef VISITABLE_H
#define VISITABLE_H

#include "IVisitor.hpp"

namespace OberonLang {
  class Visitable {
    virtual void accept(IVisitor* v) = 0; 
  };
}

#endif 
