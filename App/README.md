# Traffic Light Example – Arm FuSa RTS Process Isolation

*A practical demonstration of Arm FuSa RTS process isolation, using a simple traffic light controller to showcase safety classes, MPU zones, and fault handling on Cortex-M devices.*

## Overview

The project implements a **traffic light controller** with standard phases (red, red/yellow, green, yellow, red).

Key features include:

- **Adaptive timing**: Green phase duration depends on emulated traffic values read from a potentiometer.  
- **Process isolation**: Different software components are assigned safety integrity levels, protected using **MPU Protected Zones** and **safety classes**.  
- **Fault handling and recovery**: The system detects data errors, memory violations, or watchdog expirations and transitions to a **safe state** (yellow blinking).  
- **Web interface**: A built-in HTTP server provides live status, traffic density visualization, and controls for injecting faults.  
- **LED indicators**: On the Infineon KIT_T2G-B-H_LITE board, LEDs emulate the red and green lights.

## Safety Integration

The example demonstrates how FuSa RTS enforces **freedom from interference** between software of different safety levels:

- **Normal Operation (Class 0):** Controls light cycles and traffic data acquisition.  
- **Operation Verification (Class 0):** Validates sensor plausibility.  
- **Communication (Class 1):** Web access, monitoring, and fault injection.  
- **Safe-Mode Operation (Class 2):** Blinking yellow fallback when errors occur.

## Fault Injection and Debugging

The web interface enables triggering and observing various fault scenarios:

- Data errors (implausible sensor values).  
- Memory access violations.  
- Thread watchdog expirations.  
- Fatal kernel suspension.  

All errors are logged and visualized through the web interface and LED outputs.

## Target Hardware

The example is running on a Infineon KIT_T2G-B-H_LITE board (mounted device CYT4BF8CDS (Cortex-M0+, dual-core Cortex-M7)).

The concepts apply to **any Cortex-M device with an MPU**.

## CMSIS Solution Setup

The `T2G.csolution.yml` file contains the following projects:

- `CM0p_Boot/Boot.cproject.yml`: containing the bootloader code that starts the the Cortex-M7 cores.
- `CM7_0_TrafficLight/TrafficLight.cproject.yml`: containing the traffic light example project. Refer to the
  application's [README](./CM7_0_TrafficLight/README.md) for more information.
- `CM7_1_Blinky/Blinky.cproject.yml`: containing a simple example that blinks the third LED on the board.

---

## 🚀 Quick Start

### Build & Run

1. Clone this repository.  
1. Open the project in **Keil Studio**.
1. Build the project.
1. Flash the binary to the board.  

### Using the Example

- **LEDs** on the KIT_T2G-B-H_LITE board emulate the traffic light:
    - User LED 1: red
    - User LED 2: yellow
    - User LED 3: blinking with 2 Hz (controlled by Cortex-M7 core 1)

> Note: the green LED has been omitted as the board does not provide enough LEDs.

- **Web Interface**:  
    - Connect the board to your LAN.  
    - Open a browser and navigate to [http://traffic-light/](http://traffic-light/) or [http://<board_ip_address>/](http://<board_ip_address>/).
    - Monitor traffic status, view faults, and inject errors (data error, memory access, watchdog, fatal).

- **Safe Mode**: On error, the system transitions to blinking yellow and reports fault details via the web UI.
