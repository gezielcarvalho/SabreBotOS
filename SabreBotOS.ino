#include "ButtonController.h"
#include "IRController.h"
#include "InputManager.h"
#include "MotionManager.h"
#include "DisplayManager.h"

// Buttons
ButtonController buttons(2, 3, 4, 5, 6);

// IR receiver
IRController infrared(11);

// LCD: RS, E, D4, D5, D6, D7
DisplayManager displayManager(7, 8, 9, 10, 12, 13);

// Managers
InputManager inputManager;
MotionManager motionManager;

Command lastCommand = CMD_NONE;

void setup() {
  Serial.begin(115200);

  buttons.begin();
  infrared.begin();
  displayManager.begin();

  inputManager.addController(&buttons);
  inputManager.addController(&infrared);

  Serial.println("SabreBotOS v0.3 Ready");
  Serial.println("Controls: Buttons + IR Remote + LCD");

  displayManager.showState(CMD_STOP);
}

void loop() {
  Command command = inputManager.read();

  if (command != CMD_NONE && command != lastCommand) {
    motionManager.execute(command);
    displayManager.showState(command);

    lastCommand = command;
  }

  delay(50);
}