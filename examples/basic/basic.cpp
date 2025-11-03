#include <I2C.h>
#include <avr/io.h>

void setup() {
    // Create I2C instance with explicit pin configuration for Arduino Uno
    I2C i2c(&PINC, &DDRC, &PORTC, PC4,    // SDA pin (A4 on Arduino)
            &PINC, &DDRC, &PORTC, PC5);    // SCL pin (A5 on Arduino)

    // Optional: adjust timing if needed
    i2c.setDelay(5); // 5µs delay (default)

    // Example: Write to a device
    uint8_t deviceAddr = 0x68;  // Example device address
    uint8_t data[] = {0x00, 0x42};  // Example data
    
    if (i2c.writeMessage(deviceAddr, data, sizeof(data))) {
        // Write successful
    }
}

void loop() {
    // Your code here
}