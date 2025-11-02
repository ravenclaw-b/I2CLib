#include<I2C.h>
#include<avr/io.h>
#include<util/delay.h>


class I2C { 
    
    public:
    I2C(volatile uint8_t *sda_ddr, volatile uint8_t *sda_port, uint8_t sda_pin,
        volatile uint8_t *scl_ddr, volatile uint8_t *scl_port, uint8_t scl_pin) 
        : SDA_DDR(sda_ddr), SDA_PORT(sda_port), SDA_PIN(sda_pin),
          SCL_DDR(scl_ddr), SCL_PORT(scl_port), SCL_PIN(scl_pin) {
        
        // Initialize I2C pins
        *SDA_DDR |= (1 << SDA_PIN); // Set SDA as output
        *SCL_DDR |= (1 << SCL_PIN); // Set SCL as output
    }

    I2C() = delete; // Disable default constructor

    void setDelay(int microseconds) {
        I2C_DELAY_US = microseconds;
    }

    private:
    volatile uint8_t *SDA_DDR;
    volatile uint8_t *SDA_PORT;
    uint8_t SDA_PIN;

    volatile uint8_t *SCL_DDR;
    volatile uint8_t *SCL_PORT;
    uint8_t SCL_PIN;

    int I2C_DELAY_US = 5; // Delay in microseconds

    void pull_scl_low() {
        (*SCL_DDR) |= (1 << SCL_PIN); // Set SCL as output
        (*SCL_PORT) &= ~(1 << SCL_PIN); // Drive SCL low
    }

    void release_scl() {
        (*SCL_DDR) &= ~(1 << SCL_PIN); // Set SCL as input
        (*SCL_PORT) |= (1 << SCL_PIN); // Enable pull-up resistor on SCL
    }

    void pull_sda_low() {
        (*SDA_DDR) |= (1 << SDA_PIN); // Set SDA as output
        (*SDA_PORT) &= ~(1 << SDA_PIN); // Drive SDA low
    }

    void release_sda() {
        (*SDA_DDR) &= ~(1 << SDA_PIN); // Set SDA as input
        (*SDA_PORT) |= (1 << SDA_PIN); // Enable pull-up resistor on SDA
    }


    bool read_scl() {
        return ((*SCL_PORT) & (1 << SCL_PIN)) != 0;
    }

    bool read_sda() {
        return ((*SDA_PORT) & (1 << SDA_PIN)) != 0;
    }

    inline void delay() {
        _delay_us(5); 
    }   

    bool writeByte(uint8_t data) {
        for (int i = 0; i < 8; i++)
        {   
            pull_scl_low(); // Clock low
            delay();

            if (data & 0x80) {
                release_sda(); // Send 1
            } else {
                pull_sda_low(); // Send 0
            }
            delay();
            
            release_scl(); // Clock high
            uint32_t timeout = 10000;
            while (!read_scl() && --timeout); { }
            delay();

            data <<= 1;
        }

        // ACK/NACK bit
        pull_scl_low();
        release_sda(); // Release SDA for ACK/NAC
        delay();

        release_scl(); // Clock high
        uint32_t timeout = 10000;
        while (!read_scl() && --timeout) { }
        delay();
        
        bool ack = !read_sda(); // ACK is low (0), NACK is high (1)
        pull_scl_low();

        return ack;
    }
};