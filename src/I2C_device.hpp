#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H
#include <Arduino.h>
#include <Wire.h>

namespace i2c_driver {
class I2CDevice {
 protected:
  byte address_ = 0x00;
  TwoWire* wire_ = &Wire;

 public:
  // Initializer Functions
  I2CDevice();
  void init(byte address, TwoWire* preferred_wire = &Wire);

  // read Functions
  uint8_t readBytesFromReg(byte regadd, unsigned int count, byte* values);
  byte readByteFromReg(byte regadd, uint8_t* error_code = nullptr);
  byte readBitsFromReg(byte regadd, byte bitmask,
                       uint8_t* error_code = nullptr);
  uint8_t readShortIntsFromReg(byte regadd, unsigned int count,
                               short int* values, bool msb_first = true);
  short int readShortIntFromReg(byte regadd, bool msb_first = true,
                                uint8_t* error_code = nullptr);

  // write Functions
  uint8_t writeBytesToReg(byte regadd, unsigned int count, byte* value);
  uint8_t writeByteToReg(byte regadd, byte value);
  uint8_t writeBitsToReg(byte regadd, byte bitmask, byte value);
};
}  // namespace i2c_driver

#endif
