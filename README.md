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

## Installation

### PlatformIO

1. Add this repository to your `platformio.ini`:
```ini
lib_deps =
    https://github.com/ravenclaw-b/I2CLib.git
```

### Manual

1. Copy the `lib/I2C` folder to your project
2. Include the header in your code:
```cpp
#include "I2C.h"
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

## Building

### PlatformIO

```bash
# Build the project
pio run

# Upload to your board
pio run -t upload
```

### CMake

```bash
mkdir build && cd build
cmake ..
make
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.