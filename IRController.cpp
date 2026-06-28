#include "IRController.h"
#include <IRremote.hpp>

#define IR_FORWARD  0x18
#define IR_BACKWARD 0x52
#define IR_LEFT     0x08
#define IR_RIGHT    0x5A
#define IR_STOP     0x1C

IRController::IRController(int pin) {
  receivePin = pin;
}

void IRController::begin() {
  IrReceiver.begin(receivePin, DISABLE_LED_FEEDBACK);
}

Command IRController::read() {
  if (!IrReceiver.decode()) return CMD_NONE;

  auto data = IrReceiver.decodedIRData;

  if (data.flags & IRDATA_FLAGS_IS_REPEAT) {
    IrReceiver.resume();
    return CMD_NONE;
  }

  if (data.protocol == UNKNOWN || data.command == 0) {
    IrReceiver.resume();
    return CMD_NONE;
  }

  uint8_t cmd = data.command;
  IrReceiver.resume();

  switch (cmd) {
    case IR_FORWARD: return CMD_FORWARD;
    case IR_BACKWARD: return CMD_BACKWARD;
    case IR_LEFT: return CMD_LEFT;
    case IR_RIGHT: return CMD_RIGHT;
    case IR_STOP: return CMD_STOP;
    default: return CMD_NONE;
  }
}