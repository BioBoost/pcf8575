#pragma once

#include "mbed.h"

namespace IOExpansion {

  class PCF8575 {

    public:
      PCF8575(unsigned int address, I2C * i2c);

    public:
      void set_port_direction(unsigned int mask);
      unsigned int read(void);
      void write(unsigned int data);

    private:
      void set_all_as_inputs(void);

    private:
        unsigned int address;
        I2C * i2c;
        unsigned int directionMask;    // Outputs are 0, Inputs are 1
        const static unsigned int ALL_INPUTS = 0xFFFF;
  };

};