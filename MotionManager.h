#ifndef MOTION_MANAGER_H
#define MOTION_MANAGER_H

#include <Arduino.h>
#include "Command.h"

class MotionManager {
private:
  Command currentState;

public:
  MotionManager();
  void execute(Command command);
  Command getState();
  void printState();
};

#endif