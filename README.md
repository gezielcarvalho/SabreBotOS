# SabreBotOS

> A modular, layered robotics operating system for Arduino — designed to grow from a simple tracked robot into a full autonomous platform.

![Version](https://img.shields.io/badge/version-0.3-blue)
![Platform](https://img.shields.io/badge/platform-Arduino%20UNO-teal)
![Status](https://img.shields.io/badge/status-tested%20%26%20working-brightgreen)
![License](https://img.shields.io/badge/license-MIT-lightgrey)

---

## Table of Contents

- [SabreBotOS](#sabrebotos)
  - [Table of Contents](#table-of-contents)
  - [Vision](#vision)
  - [Architecture](#architecture)
  - [Command Flow](#command-flow)
  - [Project Structure](#project-structure)
  - [Module Reference](#module-reference)
    - [`Command.h`](#commandh)
    - [`IController.h`](#icontrollerh)
    - [`ButtonController`](#buttoncontroller)
    - [`IRController`](#ircontroller)
    - [`InputManager`](#inputmanager)
    - [`MotionManager`](#motionmanager)
    - [`DisplayManager`](#displaymanager)
  - [Hardware Setup](#hardware-setup)
    - [Components](#components)
    - [Wiring](#wiring)
  - [Getting Started](#getting-started)
  - [Design Principles](#design-principles)
    - [Single Responsibility](#single-responsibility)
    - [Hardware Independence](#hardware-independence)
    - [Open for Extension](#open-for-extension)
  - [Roadmap](#roadmap)
  - [Long-Term Vision](#long-term-vision)

---

## Vision

SabreBotOS is a layered robotics framework built around a single idea: **separate concerns so the robot can grow without rewriting**.

Instead of one monolithic sketch, every responsibility lives in its own module. Input sources, motion logic, and hardware abstraction are decoupled from the start — so adding WiFi, AI, or a camera never breaks what already works.

**Current capability (v0.3):**

```
Buttons / IR Remote
        ↓
   InputManager
        ↓
  MotionManager
        ↓
  Serial Output + LCD Display
```

**Planned future layers:** motor drivers · LCD · WiFi · ESP32 · Raspberry Pi · local AI · cloud AI · cameras · voice · autonomous navigation · robot arm · multi-robot coordination

---

## Architecture

```
┌─────────────────────────────────────────┐
│               SabreBotOS.ino            │
└───────────────────┬─────────────────────┘
                    │
          ┌─────────▼──────────┐
          │    InputManager    │  ← up to 5 controllers
          └──────┬──────┬──────┘
                 │      │
   ┌─────────────▼┐    ┌▼─────────────┐
   │ButtonController│  │ IRController │
   └─────────────┬─┘   └─────┬────────┘
                 └─────┬─────┘
                  Command
                    │     │
          ┌─────────▼──┐  └──────────────────┐
          │MotionManager│             ┌───────▼────────┐
          └─────────────┘             │ DisplayManager │
                 │                    │  (LCD 16×2)    │
          ┌──────▼──────┐             └────────────────┘
          │Motor Driver │
          │   (TBD)     │
          └─────────────┘
```

`MotionManager` never knows whether a command came from a button, IR remote, WiFi, joystick, or AI — they all speak the same `Command` language.

---

## Command Flow

Both input sources follow identical paths through the system:

```
Button Press          IR Signal
     │                    │
     ▼                    ▼
ButtonController      IRController
     │                    │
     └──────────┬──────────┘
                ▼
           InputManager
          (first non-CMD_NONE wins)
                │
                ▼  (only fires on state change)
          MotionManager ──────────── DisplayManager
                │                    (LCD 16×2)
                ▼
       Serial.println(state)   ← today
       Motor PWM               ← v0.4
```

---

## Project Structure

```
SabreBotOS/
├── SabreBotOS.ino        ← Entry point: setup & loop
├── Command.h             ← Shared command enum (CMD_FORWARD, etc.)
├── IController.h         ← Abstract interface for all input devices
├── ButtonController.h
├── ButtonController.cpp  ← Digital push-button input
├── IRController.h
├── IRController.cpp      ← IR receiver input
├── InputManager.h
├── InputManager.cpp      ← Aggregates up to 5 controllers
├── MotionManager.h
├── MotionManager.cpp     ← Executes and tracks robot state
├── DisplayManager.h
├── DisplayManager.cpp    ← LCD 16×2 status display
└── README.md
```

---

## Module Reference

### `Command.h`

The shared vocabulary of the entire system. All input sources and the motion layer communicate exclusively through these values.

```cpp
enum Command {
  CMD_NONE,
  CMD_FORWARD,
  CMD_BACKWARD,
  CMD_LEFT,
  CMD_RIGHT,
  CMD_STOP
};
```

No module invents its own movement tokens — everything uses this enum.

---

### `IController.h`

Pure interface that every input device must implement. Enforces a single contract across all controllers.

```cpp
void begin();     // initialize hardware
Command read();   // return the current command (or CMD_NONE)
```

Adding a new input source (e.g. Bluetooth, joystick, AI) only requires implementing this interface.

---

### `ButtonController`

Reads five digital push buttons mapped to movement commands.

| Pin | Command      |
| --- | ------------ |
| D2  | CMD_FORWARD  |
| D3  | CMD_BACKWARD |
| D4  | CMD_LEFT     |
| D5  | CMD_RIGHT    |
| D6  | CMD_STOP     |

---

### `IRController`

Reads an IR receiver module and maps remote codes to `Command` values.

- Receive pin: **D11**
- Returns `CMD_NONE` when no signal is active

---

### `InputManager`

Polls all registered controllers in order and returns the first non-`CMD_NONE` command it finds. Supports up to **5 controllers** simultaneously.

```cpp
inputManager.addController(&buttons);
inputManager.addController(&infrared);
Command cmd = inputManager.read();
```

---

### `MotionManager`

Tracks the robot's current motion state and executes commands. In v0.3, execution means printing the state to the Serial monitor. Motor PWM output will be added in v0.4.

**Serial output example:**

```
SabreBotOS v0.3 Ready
Controls: Buttons + IR Remote + LCD
STATE: FORWARD
STATE: TURN LEFT
STATE: STOPPED
```

The main loop deduplicates commands — `MotionManager` only fires when the state actually changes.

---

### `DisplayManager`

Drives a 16×2 LCD display using the LiquidCrystal library. Shows the robot name on row 0 and the current motion state on row 1. Updates only when the state changes to avoid flicker.

| LCD Pin | Arduino Pin |
| ------- | ----------- |
| RS      | D7          |
| E       | D8          |
| D4      | D9          |
| D5      | D10         |
| D6      | D12         |
| D7      | D13         |

**Display output example:**

```
┌────────────────┐
│SabreBotOS      │
│FORWARD         │
└────────────────┘
```

State labels: `FORWARD`, `BACKWARD`, `TURN LEFT`, `TURN RIGHT`, `STOPPED`, `IDLE`.

---

## Hardware Setup

### Components

- Arduino UNO
- 5× momentary push buttons
- IR receiver module (e.g. VS1838B)
- IR remote control
- 16×2 LCD display (HD44780-compatible)

### Wiring

**Push Buttons** — connect one side to the listed pin, other side to GND (uses `INPUT_PULLUP`):

| Button   | Arduino Pin |
| -------- | ----------- |
| Forward  | D2          |
| Backward | D3          |
| Left     | D4          |
| Right    | D5          |
| Stop     | D6          |

**IR Receiver:**

| IR Module Pin | Arduino Pin |
| ------------- | ----------- |
| Signal (OUT)  | D11         |
| VCC           | 5V          |
| GND           | GND         |

**LCD Display (16×2):**

| LCD Pin | Arduino Pin |
| ------- | ----------- |
| RS      | D7          |
| E       | D8          |
| D4      | D9          |
| D5      | D10         |
| D6      | D12         |
| D7      | D13         |
| VCC     | 5V          |
| GND     | GND         |
| V0      | 10kΩ pot    |

---

## Getting Started

1. Install the **LiquidCrystal** library (included with Arduino IDE).
2. Open `SabreBotOS.ino` in the Arduino IDE.
3. Wire the hardware as described above.
4. Upload to an Arduino UNO.
5. Open the Serial Monitor at **115200 baud**.
6. Press a button or point your IR remote — state changes appear on the Serial Monitor and on the LCD.

```
SabreBotOS v0.3 Ready
Controls: Buttons + IR Remote + LCD
STATE: FORWARD
STATE: TURN RIGHT
STATE: STOPPED
```

---

## Design Principles

### Single Responsibility

Every module has exactly one job. `IRController` reads IR and returns a `Command`. It does not move motors, update an LCD, or log anything.

### Hardware Independence

`MotionManager` never knows where a command came from. Whether the source is a button, an AI model, or a cloud API — the motion layer doesn't change.

### Open for Extension

Adding a new input source only requires two files:

```
BluetoothController.h
BluetoothController.cpp
```

No existing module needs to be modified.

---

## Roadmap

| Version | Feature                             | Status  |
| ------- | ----------------------------------- | ------- |
| v0.1    | Button controller + Serial monitor  | ✅ Done |
| v0.2    | IR controller + InputManager        | ✅ Done |
| v0.3    | LCD status display                  | ✅ Done |
| v0.4    | BTS7960 motor driver (PWM output)   | Planned |
| v0.5    | Encoders + PID speed control        | Planned |
| v0.6    | ESP8266 WiFi control                | Planned |
| v0.7    | Raspberry Pi Zero (camera, sensors) | Planned |
| v1.0    | N100 AI dock + home server          | Planned |

---

## Long-Term Vision

```
          Cloud AI
              ▲
              │
   Local AI Server (N100)
              ▲
              │
   Home Automation Network
              ▲
              │
     WiFi / MQTT / ROS2
              ▲
              │
     Raspberry Pi Zero
              ▲
              │
       ESP32 (optional)
              ▲
              │
         Arduino UNO
              ▲
              │
  Motors · Sensors · Buttons · IR
```

SabreBotOS will evolve into a distributed robotics platform where the Arduino handles real-time control, the Raspberry Pi handles perception and user interaction, and a home AI server coordinates higher-level planning across multiple robots.
