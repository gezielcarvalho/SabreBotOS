#include "ButtonController.h"

ButtonController::ButtonController(int forward, int backward, int left, int right, int stop) {
  pinForward = forward;
  pinBackward = backward;
  pinLeft = left;
  pinRight = right;
  pinStop = stop;
}

void ButtonController::begin() {
  pinMode(pinForward, INPUT_PULLUP);
  pinMode(pinBackward, INPUT_PULLUP);
  pinMode(pinLeft, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);
  pinMode(pinStop, INPUT_PULLUP);
}

Command ButtonController::read() {
  if (digitalRead(pinForward) == LOW) return CMD_FORWARD;
  if (digitalRead(pinBackward) == LOW) return CMD_BACKWARD;
  if (digitalRead(pinLeft) == LOW) return CMD_LEFT;
  if (digitalRead(pinRight) == LOW) return CMD_RIGHT;
  if (digitalRead(pinStop) == LOW) return CMD_STOP;

  return CMD_NONE;
}