# Architecture and hardware boundaries

## Current components

| Component | Responsibility |
| --- | --- |
| `SabreBotOS.ino` | Initializes modules, polls inputs, deduplicates commands, and coordinates state/display updates. |
| `Command.h` | Shared movement vocabulary used across modules. |
| `IController.h` | Common controller interface. |
| `ButtonController` | Maps five digital button inputs to commands. |
| `IRController` | Maps infrared receiver signals to commands. |
| `InputManager` | Polls registered controllers and returns the first active command. |
| `MotionManager` | Tracks and reports current motion state; it does not drive motors today. |
| `DisplayManager` | Renders startup and state information to a 16×2 LCD. |

## Command flow

1. The main loop polls `InputManager`.
2. Controllers normalize their hardware signal into a `Command` value.
3. A non-empty command that differs from the last command is executed by `MotionManager` and displayed by `DisplayManager`.
4. The current motion implementation outputs state information only; future actuator behavior is intentionally outside the present implementation.

## Hardware boundary

The existing README provides prototype pin mappings for buttons, IR receiver, and LCD. Those mappings are not a universal hardware specification. Verify voltage levels, board revision, libraries, pin conflicts, wiring quality, and external component datasheets before powering a setup.

No motor driver, feedback sensor, actuator power path, battery policy, emergency stop, or enclosure design is implemented. Any future actuator integration must introduce explicit safe-state behavior rather than extending the present serial/LCD prototype implicitly.
