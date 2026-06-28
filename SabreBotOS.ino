#include "ButtonController.h"
#include "IRController.h"
#include "InputManager.h"
#include "MotionManager.h"

// Buttons
ButtonController buttons(2, 3, 4, 5, 6);

// IR receiver
IRController infrared(11);

// Managers
InputManager inputManager;
MotionManager motionManager;

Command lastCommand = CMD_NONE;

void setup() {
  Serial.begin(115200);

  buttons.begin();
  infrared.begin();

  inputManager.addController(&buttons);
  inputManager.addController(&infrared);

  Serial.println("SabreBotOS v0.2 Ready");
  Serial.println("Controls: Buttons + IR Remote");
}

void loop() {
  Command command = inputManager.read();

  if (command != CMD_NONE && command != lastCommand) {
    motionManager.execute(command);
    lastCommand = command;
  }

  delay(50);
}