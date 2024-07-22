# Cubic-Calculator

This project is a cubic equation solver using an LCD and a keypad. It allows users to input the coefficients of a quadratic equation and displays the roots of the equation on the LCD.

## Table of Contents

- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Setup Instructions](#setup-instructions)
- [Code Explanation](#code-explanation)
- [Usage](#usage)

## Overview

This project uses an Arduino to interface with a 4x3 keypad and a 16x2 LCD to solve cubic equations. Users input the coefficients of the equation, and the roots are calculated and displayed.

## Hardware Requirements

- Arduino (any compatible model)
- 16x2 LCD
- 4x3 Keypad
- Jumper wires
- Breadboard (optional)

## Software Requirements

- Arduino IDE
- LiquidCrystal library (included with Arduino IDE)
- Keypad library

## Circuit Diagram
![Screenshot 2024-07-22 210116](https://github.com/user-attachments/assets/30cf7a80-ba03-4b0f-a881-0877f4d9ef18)
### LCD Connections

| LCD Pin | Arduino Pin |
|---------|-------------|
| RS      | 12          |
| EN      | 11          |
| D4      | 5           |
| D5      | 4           |
| D6      | 3           |
| D7      | 2           |
| VSS     | GND         |
| VDD     | 5V          |
| VO      | Potentiometer (contrast control) |

### Keypad Connections

| Keypad Pin | Arduino Pin |
|------------|-------------|
| Row 1      | 8           |
| Row 2      | 9           |
| Row 3      | 10          |
| Row 4      | 7           |
| Column 1   | 6           |
| Column 2   | A2          |
| Column 3   | A1          |

## Setup Instructions

1. Connect the LCD to the Arduino as per the connection table.
2. Connect the keypad to the Arduino according to the connection table.
3. Open the Arduino IDE and install the Keypad library if not already installed.



