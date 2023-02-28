# I2C_driver
wraps the low level gory details of I2C communication  with multiple I2C port support.
* Provides user the access to read and write byte(s), words (s) from a I2C Device using class methods.
##Usage:
  * Create a I2C device object and initialise with a address and preferred_wire. preferred_wire should be a reference to Wire Object like &Wire, &Wire1, &Wire2.
  * By default &Wire is chosen.
