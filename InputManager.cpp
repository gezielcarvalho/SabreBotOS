#include "InputManager.h"

InputManager::InputManager() {
  controllerCount = 0;
}

void InputManager::addController(IController* controller) {
  if (controllerCount < 5) {
    controllers[controllerCount] = controller;
    controllerCount++;
  }
}

Command InputManager::read() {
  for (int i = 0; i < controllerCount; i++) {
    Command cmd = controllers[i]->read();
    if (cmd != CMD_NONE) {
      return cmd;
    }
  }

  return CMD_NONE;
}