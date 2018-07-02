# PCF8575 IOExpander driver for mBed

This is a basic driver for the PCF8575 IO Expander.

Check out the examples to see how to use the library.

## Requirements

You will need to enable C++11 compilation. This can be achieved by changing the three json configurations files in `code/mbed-os/tools/profiles`. Change the `cxx` section of the `GCC_ARM` config to the following:

```json
        "cxx": ["-std=gnu++11", "-fno-rtti", "-Wvla"],
```