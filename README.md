# USB Protection Device: Smart Charging and Data Security System

## Overview

This project is a hardware-based USB data blocker and smart charge controller designed to protect devices from unauthorized data transfer while charging from public or unknown USB ports. It incorporates RFID-based user authentication, device status indication via LEDs and buzzer, and logs authorized accesses to a microSD card.

## Features

* **Data Blocking:** Prevents unauthorized data transfer while charging.
* **Smart Charging:** Only power is allowed unless authentication is successful.
* **User Authentication:** RFID-based verification using MFRC522.
* **Visual & Audio Indicators:**

  * LED1 ON: Charging only
  * LED1 + LED2 ON + Buzzer: Charging with data transfer
* **MicroSD Logging:** Logs UID of authenticated users.

## Technologies Used

* STM32 Nucleo-F411RE
* Arduino IDE for development
* MFRC522 RFID Module (I2C)
* MicroSD Card Module
* 2N3904 NPN Transistors for data line control
* LEDs, Buzzer, Push Button

## Components Required

* STM32 Nucleo-F411RE
* MFRC522 RFID Reader (I2C version)
* MicroSD Card Module (SPI)
* 2 x LEDs (Red, Green)
* 1 x Buzzer
* 1 x Push Button
* 2 x 2N3904 Transistors
* USB Type-C Female Connector breakout board or cut USB cable
* Resistors: 220Ω (for LEDs), 10kΩ (for button pull-down)
* Breadboard and jumper wires

## Circuit Connections

### Power:

* VCC and GND lines from STM32 to RFID and SD Card module

### RFID (I2C):

* SDA -> D14 (PB9)
* SCL -> D15 (PB8)
* RST -> D6

### SD Card (SPI):

* MOSI -> D11 (PA7)
* MISO -> D12 (PA6)
* SCK  -> D13 (PA5)
* CS   -> D10 (PA4)

### Indicators and Button:

* LED1 (Charging) -> D2
* LED2 (Data Transfer) -> D3
* Buzzer -> D4
* Push Button -> D5

### USB Data Blocking (with 2N3904):

* USB D+ and D− from male end go to Collector of each 2N3904
* Base of each transistor connected via 1kΩ resistor to STM32 D7 and D8 respectively
* Emitter goes to D+ and D− of USB Type-C female port

## Setup Instructions

1. Upload the provided Arduino sketch to STM32 via Arduino IDE.
2. Power the board using USB or external supply.
3. Connect RFID, SD Card, LEDs, Buzzer, Button, and Transistors as per circuit.
4. Plug USB charger male end to the Type-C female port and mobile/tab to the output USB end.

## Usage

* Insert RFID card. If UID is authorized, data lines are enabled.
* When button is pressed, data transfer is allowed and indicated via buzzer and LEDs.
* If button is released, only charging is permitted.


