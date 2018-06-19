#ifndef VISITABLE_H
#define VISITABLE_H

#include "Visitor.hpp"

namespace OberonLang {
  class Visitable {
    virtual void accept(Visitor* v) = 0; 
  };
}

#endif 
