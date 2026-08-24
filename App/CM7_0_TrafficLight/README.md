# Traffic Light Example

This project demonstrates a **safety-oriented traffic light application** with multiple fault recovery mechanisms.

The example runs on the **Infineon KIT_T2G-B-H_LITE** evaluation board (device: CYT4BF8CDDQ0AESGS, core: **Cortex-M7 Core 0**).

> **Note:** This board has only three green LEDs. Two of them are repurposed to represent the **red** and **yellow** lights. The third LED is used by another Cortex-M7 core to indicate operation.

To access the Web user interface, open a browser and navigate to:

- `http://traffic-light/` or
- `http://<board_IP_address>`

## Recovery Mechanisms

The following mechanisms ensure safe operation and fault tolerance:

- **Operation Verification**: Monitors the Normal Operation. If errors are detected, the system switches to **Safe-Mode Operation**.
- **Software Watchdogs**:
    - Monitor Operation Verification timing. If violated, Safe-Mode is activated.
    - Monitor Safe-Mode timing. If violated, threads with lower safety class are suspended. If Safe-Mode still fails, the **hardware watchdog** resets the system.
- **Memory Protection**:
    - Out-of-zone memory access in Normal Operation triggers a memory fault, activating Safe-Mode and terminating the faulty threads.
    - Out-of-zone memory access in Communication triggers Safe-Mode and terminates its threads.
- **Safe-Mode Timeout**: If Safe-Mode is inactive for more than 1s, the hardware watchdog resets the system.
- **Critical Faults**: Any fault compromising Safe-Mode triggers a hardware reset.

All fault handling is implemented in **`fault.c`** module.

The system status can be monitored through the hosted Web page, which also allows injecting faults for testing recovery mechanisms.

## Safety Classes & Zones
The application is organized into safety classes and zones:

- **Safety Class 0**
    - *Zone 0*: Normal Operation thread, Input thread
    - *Zone 1*: Operation Verification thread
- **Safety Class 1**
    - *Zone 2*: Communication threads (Web Server)
    - *Zone 4*: RTOS Timer thread
- **Safety Class 2**
    - *Zone 3*: Safe-Mode Operation thread
- **Safety Class 3**
    - *Zone 5*: RTOS Idle thread

## Project Structure

### Documentation

`README.md` : Project documentation (this file)

### System

- `app_main.c` : Application main function
- `faults.c` : Fault handling implementation
- `faults.h` : Fault handling function prototypes (API)
- `hw_watchdog.h` : Hardware watchdog function prototypes (API)
- `reset_reason.h` : Reset reason definitions and function prototype (API)
- `system_defs.h` : System definitions (safety classes, lights, button)
- `zones.h` : Zone definitions and function prototypes (API)

### Safety Class 0 (Normal)

- `NormalOperation.c` : Implements the traffic light logic. The green light duration depends on the traffic sensor, simulated by the value changed by **USER button**.
- `OperationVerification.c` : Continuously verifies Normal Operation. If input data is invalid or missing, Safe-Mode is activated.

### Safety Class 1 (Communication)

- `Communication.c` : Communication stack (HTTP Server) startup
- `HTTP_Server_CGI.c` : Web callbacks providing system status and fault injection
- `index.cgi` : Main Web landing page
- `refresh.cgx` : Dynamic Web page system status updates
- *Other files* : Other Web page source files

### Safety Class 2 (Safety)

- `SafeModeOperation.c` : Implements Safe-Mode (yellow light blinking)

### Board Layer

Contains board-specific code.

Traffic Light application and board-specific code is located in the `TrafficLight` subfolder:
- `ac6_linker_script.sct.src` : Linker script for AC6

- `io_defs.h` : Header file defining lights and sensor mapping on a board
- `cmsis_nvic_virtual.h` : NVIC overrides via SVC (for access rights elevation)
- `hw_watchdog.c` : Hardware watchdog handling
- `mem_layout.h` : Memory layout
- `reset_reason.c` : Get reset reason function
- `svc_user.c` : NVIC functions implementation via SVC
- `zones.c` : Zone management functions
