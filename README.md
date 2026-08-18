# VEX Push Back - Codebase

*A modular, multithreaded control stack built with PROS for [VEX Robotics Competition](https://www.vexrobotics.com/v5/competition/vrc-current-game).*

[![PROS](https://img.shields.io/badge/built%20with-PROS-green)](https://pros.cs.purdue.edu)
[![EZ](https://img.shields.io/badge/built%20with-EZ-pink)](https://ez-robotics.github.io/EZ-Template/)

---

## Project Overview

This repository contains the **competition-ready control stack** for GATR1 (University of Florida) during the **Push Back** season. A single codebase builds for two physical robots via compile-time selection (`ROBOT_BLUE` / `ROBOT_ORANGE`):

- Scores balls into long and middle goals with robot-specific mechanisms (lever FSM on Blue; two-stage intake on Orange)
- Runs **matchload → score → wing** autonomous cycles with EZ-Template motion chaining
- Uses a **PID-tuned 8-motor chassis** with odometry, slew limiting, and boomerang planners
- Isolates **multithreaded subsystems** (Intake, Lever, Comp Timer, Screen HUD) under PROS RTOS
- Shares ports, controls, and auton lists per robot under `include/config/`

| Variant              | Intake                      | Scoring                           | Notes                           |
| -------------------- | --------------------------- | --------------------------------- | ------------------------------- |
| **Blue** (lever bot) | Single-stage bottom rollers | Lever + gate (long / middle goal) | Four-bar, wing, lever FSM       |
| **Orange** (S bot)   | Two-stage (bottom + top)    | Gate + four-bar positioning       | Score-long / score-middle modes |


---

## Key Features


| Category                      | Highlight                                                             |
| ----------------------------- | --------------------------------------------------------------------- |
| **Dual-Robot Build**          | One repo → Blue or Orange via `robot_select.hpp`                      |
| **Lever Scoring (Blue)**      | Position PID + FSM (IDLE → SCORE → RETRACT → ZERO) with gate coupling |
| **Two-Stage Intake (Orange)** | Collect / score-long / score-middle states with reverse macro         |
| **Auton Selector**            | LCD + limit-switch interface for match, elims, skills, and PID tuning |
| **PID-Driven Chassis**        | Independent drive / turn / swing / odom loops with slew-rate limiting |
| **Pneumatics API**            | HOLD / TOGGLE wrappers with optional hardware reversal                |
| **Rumble Alerts**             | Controller buzz at 20 s remaining, then 10–1 s countdown              |
| **Multithreading**            | PROS tasks isolate Intake, Lever, Screen idle, and debug HUD          |

---

## Mechanism Demos


| Clip | Behaviors Highlighted |
| ---- | --------------------- |
| ![PID drive and turn](https://media.giphy.com/media/QepbtHhxlMNnI2sTxE/giphy.gif) | PID drive and turn — chassis tracks distance and heading
| ![Matchloader](https://media.giphy.com/media/ho14DgH9yj00u7USRj/giphy.gif) | Matchloader — pneumatic arm cycles balls from the matchload station |
| ![Wing](https://media.giphy.com/media/UkwhEi5YmmKK9NMyP2/giphy.gif) | Wing — extend / retract for goal defense and ball control |


---

## High-Level Architecture

```mermaid
flowchart TD
  init["initialize"]
  auton["autonomous"]
  op["opcontrol (main loop)"]

  subgraph "Background Tasks"
    intake["IntakeController"]
    lever["LeverController (Blue)"]
    idle["ScreenIdle"]
    debug["DebugHUD"]
  end

  drive["Drive / Chassis"]
  pistons["Pistons"]
  timer["CompTimer (rumble)"]

  init --> op
  init --> auton
  init --> intake
  init --> lever
  init --> idle
  init --> debug

  op --> drive
  op --> pistons
  op --> timer
```

---

## PID Control
> *Chassis PID wrappers are configured in [`default_constants()`](src/autons/blue/config_autons.cpp) (Blue) and [`default_constants()`](src/autons/orange/config_autons.cpp) (Orange).*  
> The robot uses **independent, decoupled PID loops** for linear motion, heading hold, swing turns, and odom / boomerang angular correction.

### Control-Loop Model
```mermaid
flowchart LR
  ref["Reference<br/>(target pose)"]
  err["Error<br/>(target - actual pose)"]
  yawPID["PID<br/>(Heading/Yaw)"]
  leftPID["PID<br/>(Left Chassis)"]
  rightPID["PID<br/>(Right Chassis)"]
  combine["Combine<br/>PID Outputs"]
  volt["Motor<br/>Voltage"]
  drivetrain["Drivetrain<br/>Model"]
  meas["Actual<br/>Pose"]

  ref --> err
  meas -.-> err

  err --> yawPID
  err --> leftPID
  err --> rightPID

  yawPID --> combine
  leftPID --> combine
  rightPID --> combine

  combine --> volt
  volt --> drivetrain
  drivetrain --> meas
```

### Continuous-Time Law

$$
u(t) = K_p\,e(t) + K_i\!\!\int_{0}^{t}\! e(\tau)\,d\tau + K_d\,\frac{de(t)}{dt}
$$

### Discrete Implementation (100 Hz)

$$
u[k] = K_p\,e[k] + K_i\,\sum_{i=0}^{k} e[i]\,\Delta t + K_d\,\frac{e[k]-e[k-1]}{\Delta t}
$$

Integral term is clamped to $\pm I_{\max}$ for anti-windup.

**Blue (lever bot)** — Orange is separately tuned (drive $K_p$ 16.0, turn $K_p$ 3.5):

| Loop          |    $K_p$ | $K_i$ | $K_d$ | Notes                    |
| ------------- | -------: | ----: | ----: | ------------------------ |
| Drive dist.   | **17.4** |     0 |   170 | Slew-limited ±70 V/s     |
| Heading hold  |      8.0 |     0 |    20 | Cascaded with Drive      |
| Turn-in-place |     3.25 |  0.05 |  25.5 | Raw IMU                  |
| Swing         |      6.0 |     0 |    65 | Outer wheel only         |
| Odom θ        |      6.5 |     0 |  52.5 | Pure-pursuit / boomerang |
| Lever (Blue)  |      1.9 |     0 |  0.16 | Position to 800° score   |

---

## Building

Requires [PROS](https://pros.cs.purdue.edu/) with EZ-Template installed (see `project.pros`).

Select exactly one robot before building by copying the example header and defining either `ROBOT_BLUE` or `ROBOT_ORANGE`:

```bash
cp include/config/robot_select.hpp.example include/config/robot_select.hpp
# Edit robot_select.hpp: uncomment ROBOT_BLUE or ROBOT_ORANGE
make
```

The build fails if neither macro is defined. `robot_select.hpp` is gitignored so each machine can pick a robot locally.

---

## Project Layout

```
include/
  config/          Blue & Orange ports, controls, auton declarations
  core/            Globals, util, subsystems (drive, intake, pistons, lever, …)
  screen/          Brain LCD debug pages and idle splash
src/
  core/            main.cpp, globals, subsystem implementations
  autons/          Per-robot PID constants, selector list, routines
  screen/          Idle logo task and debug HUD
```

