#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include <Arduino.h>
#include "IController.h"

class ButtonController : public IController {
private:
  int pinForward;
  int pinBackward;
  int pinLeft;
  int pinRight;
  int pinStop;

public:
  ButtonController(int forward, int backward, int left, int right, int stop);
  void begin();
  Command read();
};

#endif