#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "IController.h"

class InputManager {
private:
  IController* controllers[5];
  int controllerCount;

public:
  InputManager();
  void addController(IController* controller);
  Command read();
};

#endif