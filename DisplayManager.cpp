#include "DisplayManager.h"

DisplayManager::DisplayManager(int rs, int enable, int d4, int d5, int d6, int d7)
  : lcd(rs, enable, d4, d5, d6, d7) {
  lastState = CMD_NONE;
}

void DisplayManager::begin() {
  lcd.begin(16, 2);
  delay(100);

  lcd.clear();
  delay(5);

  showStartup();
}

void DisplayManager::showStartup() {
  writeLine(0, "SabreBotOS");
  writeLine(1, "Ready");
}

void DisplayManager::showState(Command state) {
  if (state == lastState) return;

  lastState = state;

  writeLine(0, "SabreBotOS");
  writeLine(1, commandToText(state));
}

void DisplayManager::writeLine(int row, const char* text) {
  lcd.setCursor(0, row);

  // Clear the row manually
  lcd.print("                "); // 16 spaces

  lcd.setCursor(0, row);
  lcd.print(text);
}

const char* DisplayManager::commandToText(Command command) {
  switch (command) {
    case CMD_FORWARD:
      return "FORWARD";

    case CMD_BACKWARD:
      return "BACKWARD";

    case CMD_LEFT:
      return "TURN LEFT";

    case CMD_RIGHT:
      return "TURN RIGHT";

    case CMD_STOP:
      return "STOPPED";

    default:
      return "IDLE";
  }
}