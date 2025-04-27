
---

# I2C Read and Write for DS1307 RTC

## Overview

This project demonstrates how to interface with the DS1307 Real-Time Clock (RTC) using the I2C protocol. It provides examples of reading from and writing to the DS1307's registers using embedded C. The project is designed to work with Infineon's PSoC™ microcontrollers and utilizes the ModusToolbox™ development environment.

## Features

- **I2C Communication**: Implements I2C protocol to communicate with the DS1307 RTC.
- **Time Setting**: Allows setting the current time and date on the DS1307.
- **Time Reading**: Reads the current time and date from the DS1307.
- **Modular Code**: Separates reading and writing functionalities into distinct source files for clarity.

## Project Structure

```
I2C-READ-AND-WRITE-FOR-DS1307-RTC/
├── main_rtc_read.c   // Code to read time from DS1307
├── main_rtc_write.c  // Code to write time to DS1307
└── README.md         // Project documentation
```

## Requirements

- **Hardware**:
  - Infineon PSoC™ microcontroller development board (e.g., CY8CKIT-062-BLE)
  - DS1307 RTC module
  - I2C pull-up resistors (typically 4.7kΩ)
  - Connecting wires

- **Software**:
  - [ModusToolbox™](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/) installed on your development machine
  - Serial terminal application (e.g., PuTTY, Tera Term) for UART communication

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/ViralPatel-19/I2C-READ-AND-WRITE-FOR-DS1307-RTC.git
```

### 2. Open the Project in ModusToolbox™

- Launch **ModusToolbox™**.
- Click on **"Import Application"**.
- Navigate to the cloned repository and select the project.

### 3. Hardware Connections

Connect the DS1307 RTC module to the PSoC™ development board as follows:

- **VCC**: Connect to 3.3V or 5V power supply (depending on your board's logic level)
- **GND**: Connect to ground
- **SCL**: Connect to the I2C clock line (e.g., P6[0] on PSoC™ 6)
- **SDA**: Connect to the I2C data line (e.g., P6[1] on PSoC™ 6)

Ensure that 4.7kΩ pull-up resistors are connected between SCL/SDA lines and VCC.

### 4. Build and Program

- Choose the desired source file:
  - To write time to DS1307: `main_rtc_write.c`
  - To read time from DS1307: `main_rtc_read.c`
- Set the chosen file as the main application file.
- Build the project.
- Connect your development board via USB.
- Program the board using the **"Program"** option.

### 5. Interact with the Application

- Open your serial terminal application.
- Configure the serial port with the following settings:
  - **Baud Rate**: 115200
  - **Data Bits**: 8
  - **Parity**: None
  - **Stop Bits**: 1
  - **Flow Control**: None
- Observe the output, which will display the current time read from the DS1307 or confirm that the time has been set.

## Understanding the Code

- **main_rtc_write.c**: This file contains code to set the current time and date on the DS1307 RTC. It initializes the I2C peripheral, prepares the time data in BCD format, and writes it to the appropriate registers of the DS1307.

- **main_rtc_read.c**: This file contains code to read the current time and date from the DS1307 RTC. It initializes the I2C peripheral, reads the time data from the DS1307's registers, converts it from BCD to decimal format, and displays it via UART.

## Notes

- The DS1307 stores time data in Binary-Coded Decimal (BCD) format. Ensure proper conversion between BCD and decimal when reading from or writing to the RTC.

- The DS1307 operates over I2C and has a fixed slave address of 0x68.

- For accurate timekeeping, connect a 32.768 kHz crystal oscillator to the DS1307's X1 and X2 pins, and a backup battery to the VBAT pin.

## License

This project is open-source and available for educational and personal development use. Please refer to the `LICENSE` file for more information.

## Acknowledgments

- **Developed by**: Viral Patel
- **Tools Used**: ModusToolbox™, Infineon PSoC™ microcontrollers.

Feel free to contribute to this project by submitting issues or pull requests. Your feedback and improvements are welcome!

--- 
