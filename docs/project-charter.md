# Prototype charter and safety boundaries

## Objective

Explore a modular robotics-control architecture in which different input devices issue a common command vocabulary without directly depending on the display or future motor driver.

## Scope represented today

- Arduino sketch orchestration.
- Button and infrared controller modules.
- Input aggregation and a shared movement-command enum.
- Motion-state tracking/serial feedback.
- 16×2 LCD status feedback.

## Not in scope

- Motor actuation, encoder feedback, PID control, obstacle sensing, navigation, autonomy, or AI control.
- Emergency-stop circuitry, power management, fault detection, watchdog policy, or functional-safety design.
- Wireless/cloud control, user identity, remote authorization, telemetry, or multi-robot coordination.
- Production manufacturing, enclosure, certification, deployment, or field support.

## Safety and ownership gate

The prototype is for controlled bench experimentation only. Any connection to motors, batteries, actuators, or remote control requires an owner-approved electrical and physical-safety plan. Do not treat the command state or LCD display as a motor-safety mechanism.

## Future evolution criteria

1. Document a power, motor-driver, wiring, fusing, and emergency-stop design before actuator integration.
2. Add explicit fail-safe state, watchdog behavior, command timeout, and input-error handling.
3. Add hardware-in-the-loop verification and an evidence record for each supported configuration.
4. Define firmware build/toolchain versions, CI checks, and release tagging.
5. Scope networking/autonomy/security as separate reviewed capabilities.
