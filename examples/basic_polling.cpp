#include "mbed.h"
#include "pcf8575.h"

DigitalOut alive(LED1);
Serial pc(USBTX, USBRX);    // tx, rx

// main() runs in its own thread in the OS
int main() {

    I2C i2c(PTE25, PTE24);
    i2c.frequency(400000);
    IOExpansion::PCF8575 expander(0x40, &i2c);

    expander.set_port_direction(0x03FF);
    expander.write(0x0000);

    pc.baud(115200);
    printf("Starting basic polling example of the PCF8575 IO Expander\n");

    while (true) {
        alive = !alive;
        wait(0.5);
        printf("Current status of IO Expander: %d\n", expander.read());
    }
}