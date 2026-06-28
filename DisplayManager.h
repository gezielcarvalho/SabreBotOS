#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Command.h"

class DisplayManager {
private:
  LiquidCrystal lcd;
  Command lastState;

  void writeLine(int row, const char* text);

public:
  DisplayManager(int rs, int enable, int d4, int d5, int d6, int d7);

  void begin();
  void showStartup();
  void showState(Command state);
  const char* commandToText(Command command);
};

#endif