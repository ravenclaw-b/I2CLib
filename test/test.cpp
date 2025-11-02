#include <Arduino.h>
#include <I2C.h>

// MPU6050 constants
#define MPU6050_ADDRESS 0x68
#define WHO_AM_I        0x75
#define PWR_MGMT_1      0x6B
#define GYRO_XOUT_H     0x43  // High byte of gyroscope X-axis data

// Use explicit constructor: pass PINx, DDRx, PORTx pointers in that order.
// SDA -> Arduino D7 (PD7): PIND, DDRD, PORTD, PD7
// SCL -> Arduino D8 (PB0): PINB, DDRB, PORTB, PB0
I2C i2c(&PIND, &DDRD, &PORTD, PD7,
        &PINB, &DDRB, &PORTB, PB0);

void setup() {
    Serial.begin(9600);
    while (!Serial) { } // safe on boards that need serial ready
    Serial.println("I2C Bit-Banged MPU6050 Example (Gyroscope X)");

    // small delay to let sensor power up
    delay(100);

    // configure bit-banged speed (microseconds per half-cycle)
    i2c.setDelay(5);

    // Wake up the MPU6050 (clear sleep bit)
    uint8_t wakeData[] = { PWR_MGMT_1, 0x00 };
    if (!i2c.writeMessage(MPU6050_ADDRESS, wakeData, 2)) {
        Serial.println("Failed to write wakeup (PWR_MGMT_1). Check wiring.");
        // continue to attempt WHO_AM_I read for debugging
    } else {
        delay(10);
    }

    // Read WHO_AM_I register
    uint8_t reg = WHO_AM_I;
    uint8_t whoami = 0;

    if (!i2c.writeMessage(MPU6050_ADDRESS, &reg, 1)) {
        Serial.println("Write WHO_AM_I register address failed");
    } else {
        if (!i2c.readMessage(MPU6050_ADDRESS, &whoami, 1)) {
            Serial.println("Read WHO_AM_I failed");
        } else {
            Serial.print("WHO_AM_I = 0x");
            Serial.println(whoami, HEX);
            if (whoami != 0x68 && whoami != 0x69) {
                Serial.println("MPU6050 not detected (unexpected WHO_AM_I). Check AD0 pin and wiring.");
            } else {
                Serial.println("MPU6050 detected.");
            }
        }
    }
}

void loop() {
    uint8_t reg = GYRO_XOUT_H;
    uint8_t data[2] = {0};

    // Write register address, then read 2 bytes for GYRO_XOUT (high and low)
    if (!i2c.writeMessage(MPU6050_ADDRESS, &reg, 1)) {
        Serial.println("Write GYRO_XOUT_H failed");
        delay(500);
        return;
    }

    if (!i2c.readMessage(MPU6050_ADDRESS, data, 2)) {
        Serial.println("Read GYRO_XOUT_H failed");
        delay(500);
        return;
    }

    // Combine high and low bytes (signed 16-bit)
    int16_t gyroX = (int16_t)((data[0] << 8) | data[1]);

    Serial.print("Gyro X: ");
    Serial.println(gyroX);

    delay(200);
}
