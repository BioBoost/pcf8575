#include "pcf8575.h"

#ifdef DO_SIMPLE_LOG
#include "logger.h"
#endif

namespace IOExpansion {

  PCF8575::PCF8575(unsigned int address, I2C * i2c) {
      this->address = address;
      this->i2c = i2c;

#ifdef DO_SIMPLE_LOG
      Log.info("Initializing PCF8575");
#endif

      set_all_as_inputs();
      write(0xFFFF);
  }

  unsigned int PCF8575::read(void) {
    char buffer[2];
    if (i2c->read(address, buffer, sizeof(buffer))) {
#ifdef DO_SIMPLE_LOG
      Log.warning("Failed to read from PCF8575");
#endif
      return 0;
    };
    return ((buffer[1] << 8) | buffer[0]);
  }

  void PCF8575::write(unsigned int data) {
    // Inputs should stay 1, only outputs can change
    unsigned int output = data | directionMask;

    char buffer[2];
    buffer[0] = output;
    buffer[1] = (output >> 8);
    if (i2c->write(address, buffer, sizeof(buffer))) {
#ifdef DO_SIMPLE_LOG
      Log.warning("Failed to write to PCF8575");
#endif
    };
  }

  // Set 1 for inputs and 0 for outputs
  void PCF8575::set_port_direction(unsigned int mask) {
    this->directionMask = mask;
  }

  void PCF8575::set_all_as_inputs(void) {
    set_port_direction(ALL_INPUTS);
  }

};