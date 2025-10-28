# Interrupt Controller Simulation (C Program)

This project simulates an **Interrupt Controller System** in C using **Windows threads (Win32 API)**.  
It demonstrates how hardware interrupts from devices such as a **Keyboard**, **Mouse**, and **Printer** are handled, masked, or ignored based on their enabled/disabled status.

---

## 🧠 Concept Overview

In real operating systems, devices send interrupt signals to the CPU when they need attention.  
Here, each device runs as a **separate thread** that randomly triggers interrupts.  
The controller decides whether to **handle** or **ignore** the interrupt based on whether it’s **enabled (unmasked)** or **disabled (masked)**.

---

## ⚙️ Features

- Simulates **asynchronous interrupts** from Keyboard, Mouse, and Printer.  
- Supports **masking/unmasking** of device interrupts.  
- Logs all interrupt events with **timestamps** in a log file.  
- Uses **mutex** for synchronization to prevent race conditions.  
- Runs for a fixed simulation period (20 seconds).

---

## 🧩 Devices Configuration

| Device   | Default State | Description                          |
|-----------|----------------|--------------------------------------|
| Keyboard | Enabled         | High priority device (active)       |
| Mouse    | Masked (Disabled) | Medium priority device (ignored)   |
| Printer  | Enabled         | Low priority device (active)        |

----

