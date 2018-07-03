#pragma once

#include "mbed.h"
#include "mbed_events.h"

namespace IOExpansion {

  class PCF8575 {

    public:
      PCF8575(unsigned int address, I2C * i2c);
      PCF8575(unsigned int address, I2C * i2c, PinName interruptPin);
      virtual ~PCF8575(void);

    public:
      void set_port_direction(unsigned int mask);
      void register_callback(Callback<void()> func);
    
    public:
      unsigned int read(void);
      void write(unsigned int data);

    private:
      void set_all_as_inputs(void);

    private:
      unsigned int address;
      I2C * i2c;
      unsigned int directionMask;    // Outputs are 0, Inputs are 1
      const static unsigned int ALL_INPUTS = 0xFFFF;

      // Interrupt stuff
      static const unsigned int QUEUE_SIZE = 4;
      InterruptIn * interrupt;
      Callback<void()> externalCallback;
      EventQueue * queue;
      Thread eventDispatchThread;
  };

};