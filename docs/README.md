# Current-state documentation

## Purpose

SabreBotOS is a modular Arduino UNO prototype for translating button and infrared-remote commands into a shared motion state, serial output, and LCD status display. It demonstrates separation of hardware input, command normalization, and output responsibilities.

## Current state

- Platform: Arduino UNO-style sketch and C++ modules.
- Inputs: five pull-up buttons and an infrared receiver.
- Command flow: controller implementations → `InputManager` → shared `Command` enum → `MotionManager`/`DisplayManager`.
- Outputs: serial state messages and a 16×2 LCD.
- Motion: `MotionManager` currently tracks/prints state; motor driver/PWM output is planned, not implemented.
- Verification: no automated host-side or hardware-in-the-loop test suite, CI, wiring validation record, or release process was found.

## Decision

Retain as a supporting embedded-systems and modular-design reference. It can demonstrate architecture and hardware-prototype thinking, but must not be described as an autonomous or safety-critical robotics platform.

See the [prototype charter](project-charter.md), [architecture/hardware guide](architecture.md), and [quality handoff](delivery-and-quality.md).
