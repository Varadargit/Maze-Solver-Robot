# Maze Solver Robot

Autonomous differential-drive robot designed to navigate **unknown maze environments** using real-time IR and ultrasonic sensing with a sensor-based wall-following navigation approach. Built using an **Arduino Uno, L298N motor driver, two DC motors, two IR sensors, and one ultrasonic sensor**.

Developed as a practical robotics project and used for participation in the **Technoxian World Robotic Competition**.

## Overview

The robot continuously processes sensor readings to understand its surrounding environment and determine the appropriate movement.

* **IR sensors:** Detect nearby walls or obstacles on the left and right sides.
* **Ultrasonic sensor:** Measures the distance to obstacles in front of the robot.
* **Arduino Uno:** Processes sensor inputs and executes the navigation logic.
* **L298N:** Controls the direction of the two DC motors.
* **Differential drive:** Allows the robot to move forward and perform left and right turns.

The robot does not rely on a predefined maze map. Navigation decisions are made from the sensor information available at the current position.
---

## Hardware Architecture

| **Component**       | **Implementation**  | **Function**                             |
| ------------------- | ------------------- | ---------------------------------------- |
| **Microcontroller** | Arduino Uno         | Sensor processing and navigation control |
| **Motor Driver**    | L298N Dual H-Bridge | Direction control for DC motors          |
| **Actuators**       | 2x DC Motors        | Differential-drive movement              |
| **Side Sensors**    | 2x IR Sensors       | Left and right wall/obstacle detection   |
| **Front Sensor**    | Ultrasonic Sensor   | Front obstacle distance measurement      |
| **Support**         | Caster Wheel        | Front support and balance                |
| **Chassis**         | Robot chassis       | Mechanical structure                     |

## Navigation Strategy

The robot follows a **sensor-based wall-following approach**.

At each control cycle, the Arduino:

1. Reads the left IR sensor.
2. Reads the right IR sensor.
3. Measures the front obstacle distance.
4. Evaluates the current path.
5. Selects a movement command.
6. Drives the motors.
7. Repeats the process.

```text
                Sensor Input
                     │
        ┌────────────┼────────────┐
        ▼            ▼            ▼
     Left IR      Ultrasonic    Right IR
        │            │            │
        └────────────┼────────────┘
                     ▼
              Arduino Uno
                     │
                     ▼
             Navigation Logic
                     │
          ┌──────────┼──────────┐
          ▼          ▼          ▼
       Forward      Left       Right
          │          │          │
          └──────────┼──────────┘
                     ▼
                Motor Driver
                     │
                     ▼
                 Robot Motion
                     │
                     └──────► Repeat
```

---

## Control Logic

The navigation logic uses the current sensor state to select the robot's movement.

### Forward Movement

When the front path is sufficiently clear, the robot continues moving forward.

### Left / Right Navigation

When the forward path is blocked, the side IR sensor readings are used to determine the available direction.

### Obstacle Detection

The ultrasonic sensor provides the front distance measurement used to identify an obstacle in the robot's path.

### Continuous Navigation

After executing a movement, the robot returns to sensor reading and evaluates the environment again.

```text
Read Sensors
     │
     ▼
Front Path Clear?
   │         │
  YES        NO
   │         │
   ▼         ▼
Forward   Check Side Sensors
             │
       ┌─────┴─────┐
       ▼           ▼
    Left Path    Right Path
       │           │
       ▼           ▼
    Turn Left   Turn Right
       │           │
       └─────┬─────┘
             ▼
       Read Sensors Again
```

> **Note:** Exact IR sensor polarity, distance threshold, and turning duration depend on the sensor modules and physical robot calibration.

---

## Differential Drive

The robot uses two independently controlled DC motors.

```text
                  FRONT
                    ↑

             ┌─────────────┐
             │  Ultrasonic │
             └──────┬──────┘
                    │
          IR    ┌───┴───┐    IR
         LEFT   │Arduino│   RIGHT
                │  Uno  │
                └───┬───┘
                    │
              ┌─────┴─────┐
              │  Chassis  │
              └───────────┘
                  ○     ○
                Left   Right
                Motor  Motor

                    ○
                  Caster
```

* **Forward:** Both drive motors rotate forward.
* **Left turn:** Motor directions are controlled to rotate the robot toward the left.
* **Right turn:** Motor directions are controlled to rotate the robot toward the right.
* **Stop:** Both motors are stopped.

---

## Software Architecture

The Arduino program is organized into separate functional components:

```text
MazeSolver.ino
│
├── Sensor Initialization
│   ├── Left IR
│   ├── Right IR
│   └── Ultrasonic
│
├── Sensor Reading
│   ├── IR State
│   └── Distance Measurement
│
├── Navigation Logic
│   └── Movement Decision
│
├── Motor Control
│   ├── Forward
│   ├── Left
│   ├── Right
│   └── Stop
│
└── Main Control Loop
```

The main execution cycle follows:

```text
Initialize
    ↓
Read Sensors
    ↓
Process Sensor Data
    ↓
Determine Movement
    ↓
Control Motors
    ↓
Repeat
```

---

## Repository Structure

```text
Maze-Solver-Robot/
│
├── Arduino/
│   └── MazeSolver/
│       └── MazeSolver.ino
│
├── docs/
│   ├── project-flow.md
│   └── wiring.md
│
├── images/
│   ├── robot.jpg
│   ├── maze-solving.png
│   ├── circuit.png
│   └── architecture.png
│
├── README.md
└── .gitignore
```

---

## Testing & Calibration

The robot requires physical calibration before autonomous operation.

* Tested IR sensors to verify their response to nearby walls and obstacles.
* Tested the ultrasonic sensor for front-distance measurement.
* Verified individual motor directions through the L298N driver.
* Tested forward movement and turning behavior.
* Adjusted navigation parameters based on the physical robot response.
* Tested the robot progressively from simple paths to more complex maze sections.

---

## Challenges

* **Sensor variability:** IR sensor readings can change depending on wall distance, surface properties, and sensor orientation.
* **Turning accuracy:** Motor timing and wheel traction affect the accuracy of robot turns.
* **Battery effects:** Motor behavior can change as battery voltage changes.
* **Real-time decisions:** The robot must make navigation decisions using only its current sensor readings.
* **Hardware integration:** Sensor, controller, motor driver, and motors must operate together reliably.

---

## Competition Experience

The Maze Solver Robot was developed as a practical robotics project and used for participation in the **Technoxian World Robotic Competition**.

The project provided hands-on experience with:

* Autonomous robot navigation.
* Sensor interfacing.
* Embedded programming.
* Motor control.
* Hardware-software integration.
* Sensor calibration.
* Physical robot testing and debugging.

---

## Technologies

| Category            | Technologies                           |
| ------------------- | -------------------------------------- |
| **Microcontroller** | Arduino Uno                            |
| **Programming**     | C/C++                                  |
| **Sensors**         | IR, Ultrasonic                         |
| **Motor Driver**    | L298N                                  |
| **Actuators**       | DC Motors                              |
| **Navigation**      | Sensor-based Wall Following            |
| **Robotics**        | Differential Drive, Obstacle Detection |
| **Development**     | Arduino IDE                            |

---

## Future Improvements

* Add wheel encoders for movement feedback.
* Improve turning accuracy using closed-loop control.
* Add additional distance sensors for better environmental perception.
* Implement maze mapping and path storage.
* Implement shortest-path planning after maze exploration.
* Add wireless telemetry for real-time sensor monitoring.
* Develop a simulation environment for testing navigation algorithms.

---

## Key Takeaways

* Built an autonomous robot capable of making navigation decisions from real-time sensor input.
* Gained hands-on experience with Arduino-based embedded systems.
* Integrated IR and ultrasonic sensors with motor control hardware.
* Implemented a sensor-based navigation strategy for an unknown environment.
* Worked with differential-drive motion and real-world robot calibration.
* Gained practical robotics experience through competition-oriented development.
