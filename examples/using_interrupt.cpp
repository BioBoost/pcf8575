#include "mbed.h"
#include "pcf8575.h"

DigitalOut alive(LED1);
Serial pc(USBTX, USBRX);    // tx, rx

IOExpansion::PCF8575 * expander;

void isr(void) {
    // Safe to read as driver uses internal EventQueue
    printf("Current status of IO Expander: %d\n", expander->read());
}

// main() runs in its own thread in the OS
int main() {
    pc.baud(115200);
    printf("Starting interrupt example of the PCF8575 IO Expander\n");

    I2C i2c(PTE25, PTE24);
    i2c.frequency(400000);
    expander = new IOExpansion::PCF8575(0x40, &i2c, PTC0);

    expander->set_port_direction(0x03FF);
    expander->write(0x0000);
    expander->register_callback(isr);

    while (true) {
        alive = !alive;
        wait(0.5);
    }
}
