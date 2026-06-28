#include "MotionManager.h"

MotionManager::MotionManager() {
  currentState = CMD_STOP;
}

void MotionManager::execute(Command command) {
  if (command == CMD_NONE) return;

  currentState = command;
  printState();
}

Command MotionManager::getState() {
  return currentState;
}

void MotionManager::printState() {
  switch (currentState) {
    case CMD_FORWARD:
      Serial.println("STATE: FORWARD");
      break;
    case CMD_BACKWARD:
      Serial.println("STATE: BACKWARD");
      break;
    case CMD_LEFT:
      Serial.println("STATE: TURN LEFT");
      break;
    case CMD_RIGHT:
      Serial.println("STATE: TURN RIGHT");
      break;
    case CMD_STOP:
      Serial.println("STATE: STOPPED");
      break;
    default:
      break;
  }
}