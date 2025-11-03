# I2CLib

A flexible, pin-configurable I2C master library for AVR microcontrollers that implements the I2C/TWI protocol through software bit-banging. Supports one master communicating with multiple slave devices using any GPIO pins.

## Features

- Software I2C implementation (bit-banged)
- One master, multiple slaves architecture
- Configurable pins - use any GPIO pins for SDA and SCL
- Adjustable timing for different clock speeds
- Support for both reading and writing I2C messages
- Timeout protection for clock stretching
- Works with Arduino framework or bare AVR

## Getting Started

### Installation Options

#### Option 1: Using PlatformIO 

1. Install [PlatformIO](https://platformio.org/) for your preferred IDE (VS Code recommended)
2. Create or open your PlatformIO project
3. Add this repository to your `platformio.ini`:
   ```ini
   lib_deps =
       https://github.com/ravenclaw-b/I2CLib.git
   ```
4. PlatformIO will automatically download and install the library when you build your project

#### Option 2: Manual Installation

1. Download the library:
   - Visit [https://github.com/ravenclaw-b/I2CLib](https://github.com/ravenclaw-b/I2CLib)
   - Click the green "Code" button and select "Download ZIP"
   - Extract the ZIP file
2. Copy the files:
   - Navigate to the extracted folder
   - Copy the entire `lib/I2C` folder to your project's library directory
3. Include the library in your code:
   ```cpp
   #include "I2C.h"
   ```

### Building Your Project

#### Using PlatformIO

1. Open your project in VS Code with PlatformIO extension installed
2. Configure your `platformio.ini` for your board:
   ```ini
   [env:your_board]
   platform = atmelavr
   board = atmega328p  ; or your specific board
   framework = arduino ; if using Arduino framework
   lib_deps =
       https://github.com/ravenclaw-b/I2CLib.git
   ```
3. Build the project:
   - Click the PlatformIO Build button in VS Code
   - Or use the command: `pio run`

#### Manual Build (AVR-GCC)

1. Include the library headers in your source files
2. Compile with AVR-GCC:
   ```bash
   avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -o main.elf main.cpp I2C.cpp
   ```
3. Create hex file:
   ```bash
   avr-objcopy -O ihex main.elf main.hex
   ```

## Usage

### Basic Setup

```cpp
#include "I2C.h"
#include <avr/io.h>

// Create I2C instance with explicit pin configuration
I2C i2c(&PINC, &DDRC, &PORTC, PC4,    // SDA pin (A4 on Arduino)
        &PINC, &DDRC, &PORTC, PC5);    // SCL pin (A5 on Arduino)

// Optional: adjust timing if needed
i2c.setDelay(5); // 5µs delay (default)
```

### Writing Data

```cpp
uint8_t deviceAddr = 0x68;  // Device address
uint8_t data[] = {0x00, 0x42};  // Data to send

if (i2c.writeMessage(deviceAddr, data, sizeof(data))) {
    // Write successful
} else {
    // Error handling
}
```

### Reading Data

```cpp
uint8_t deviceAddr = 0x68;  // Device address
uint8_t data[2];           // Buffer for received data

if (i2c.readMessage(deviceAddr, data, sizeof(data))) {
    // Read successful
    // data[0] and data[1] contain received bytes
} else {
    // Error handling
}
```

## Pin Configuration

The library supports two constructor variants:

1. **Preferred (Explicit PINx Register)**
```cpp
I2C(volatile uint8_t *sda_pin_reg, volatile uint8_t *sda_ddr, volatile uint8_t *sda_port, uint8_t sda_pin,
    volatile uint8_t *scl_pin_reg, volatile uint8_t *scl_ddr, volatile uint8_t *scl_port, uint8_t scl_pin);
```

2. **Backwards Compatible**
```cpp
I2C(volatile uint8_t *sda_ddr, volatile uint8_t *sda_port, uint8_t sda_pin,
    volatile uint8_t *scl_ddr, volatile uint8_t *scl_port, uint8_t scl_pin);
```

### Example Pin Configurations

#### Arduino Uno (ATmega328P)
```cpp
// Using Arduino pins A4 (SDA) and A5 (SCL)
I2C i2c(&PINC, &DDRC, &PORTC, PC4,    // SDA on A4
        &PINC, &DDRC, &PORTC, PC5);    // SCL on A5
```

#### Custom Pins
```cpp
// Using any pins (example: PB0 and PB1)
I2C i2c(&PINB, &DDRB, &PORTB, PB0,    // SDA on PB0
        &PINB, &DDRB, &PORTB, PB1);    // SCL on PB1
```

## Building and Uploading

### With PlatformIO

```bash
# Build the project
pio run

# Upload to your board
pio run -t upload

# Monitor serial output
pio device monitor
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.