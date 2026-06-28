#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "Command.h"

class IController {
public:
  virtual Command read() = 0;
};

#endif