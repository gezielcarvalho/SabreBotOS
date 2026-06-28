#ifndef IR_CONTROLLER_H
#define IR_CONTROLLER_H

#include <Arduino.h>
#include "IController.h"

class IRController : public IController {
private:
  int receivePin;

public:
  IRController(int pin);
  void begin();
  Command read();
};

#endif