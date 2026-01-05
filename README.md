# Altitude Threshold Alert System 🛰️

## Overview
An embedded systems project developed for my Computer Engineering Seminar at UMass Amherst. This system utilizes a BMP180 barometric pressure sensor to track relative altitude changes and triggers a physical LED alert when a 5-foot vertical threshold is surpassed.


## Engineering Challenge
The primary challenge of this project was managing **atmospheric noise** and **sensor jitter**. Barometric pressure fluctuates constantly; a simple "if altitude > 5" check would cause the LED to flicker rapidly. 

### Solutions Implemented:
- **Baseline Calibration:** On startup, the system takes 50 samples to establish a stable "ground level" reference point.
- **Signal Averaging:** During operation, the code continuously averages 10 samples per loop to filter out noise from air currents.
- **Hysteresis Logic:** I implemented separate "On" (5ft) and "Off" (4.8ft) thresholds. This prevents "chatter" when the device is held exactly at the threshold height.

## Bill of Materials (BOM)
- **Controller:** Arduino UNO R3
- **Sensor:** BMP180 (I2C Protocol)
- **Alerts:** Red LED with 220Ω current-limiting resistor
- **Power:** 9V DC Battery for portability
