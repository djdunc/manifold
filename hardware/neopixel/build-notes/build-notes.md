
LED Strips: 4x 5m WS2812B (60 LEDs/m). Total: 1,200 Pixels. Each pixel max 60mA at full white, full brightness. Typical RGB load is 20mA.

Current Limit (Software): WLED Software Power Limiter set to 30A max current draw for system.

Data Flow: Output Pin 1: 600 LEDs (Strips 1 & 2), Reversed in software. Output Pin 2: 600 LEDs (Strips 3 & 4).

Shielding: 50mm minimum clearance between the 5V DC power cables and the Data signal wires on LED strips to prevent Electromagnetic Interference.

Main Power Supply: 5V DC, 60A (300W). Input AC voltage 230V AC grounded (earthed) AC plug.

Fuses: Four 10A or 15A Blade Fuses on each 5m injection leg.

Wiring: 3-core cable for 5V power to end of LED strip and ground circuit. Note mapping: Brown = 5V, Blue = GND, Green/Yellow = GND (doubled up).

Microcontroller: ESP32-S3 (Powered via 5V/GND pins).

Logic Level Shifter: Adafruit 757 (BSS138).
Low Side (LV): 3.3V (from ESP32 3V3 pin).
High Side (HV): 5V (from 60A PSU).

Data Resistors: 330Ω. Place in series between the Level Shifter output and the start of the LED data lines.

Smoothing Capacitors: 1000µF, 10V Electrolytic. Place at each of the four main power injection points.

# Parts list:

Based on our final design for the 20-meter / 1,200 LED installation (using the 60A PSU and central ESP32-S3), here is your summarized parts list:

1. Core Controller & Signal

Microcontroller: ESP32-S3 Zero (or similar S3-based board).

Logic Level Shifter: Adafruit 757 (4-channel Bi-directional BSS138).

Resistors: 2x 330Ω to 470Ω (1/4 Watt) – one for each of the two data outputs.

Signal Protection: Small 0.1µF ceramic and 10µF electrolytic capacitors (to filter power near the ESP32).

2. Power Supply & Protection

Main PSU: 5V DC, 60A (300W) industrial enclosed power supply.

Master Fuse: 1x 40A or 50A automotive-style fuse (for the main 5V output).

Branch Fuses: 4x 10A or 15A automotive blade fuses (one for each 5m injection leg).

Filter Capacitors: 4x 1000µF (6.3V or 10V) electrolytic capacitors – placed at each of the 4 power injection points.

3. LEDs & Cabling

LED Strips: 4x 5m WS2812B 60 LEDs/meter (IP67 rated). Total 1,200 LEDs.

Power Injection Cable: Standard 3-core mains cable (approx. 1.0mm² to 1.5mm²).

Note: Use Brown for 5V, Blue for GND, and Green/Yellow for GND (doubled up).

Terminal Blocks: A few 3-way or 5-way screw terminals (for AC input and DC branching).

4. Software Logic Settings (WLED)

Pin 1: 600 LEDs (Left half, Reversed).

Pin 2: 600 LEDs (Right half).

Current Limiter: Set to 30,000mA (30A) to protect the strips and keep the 60A PSU running cool.

Electrician's Labeling Summary

If you are putting this into Fusion 360 for sign-off, label the cables as 1.0mm² or 1.5mm² copper and the power rail as a "Common Ground Star Topology."
