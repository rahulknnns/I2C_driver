#include "I2C_device.hpp"
namespace i2c_driver {
/**
 * @brief Construct a new I2CDevice::I2CDevice object
 */
I2CDevice::I2CDevice() {}

/**
 * @brief Set up the parameters I2C device
 * @param address I2C address of the device 0 - 127
 * @param preferred_wire I2C port to use e.g. Wire, Wire1, Wire2
 */
void I2CDevice::init(byte address, TwoWire* preferred_wire) {
  address_ = address;
  if (preferred_wire != nullptr) {
    wire_ = preferred_wire;
  }
}

/**
 * @brief Read bytes from a register location
 * @param regadd register address
 * @param count number of bytes to read
 * @param values pointer to the array of bytes to store the read values
 * @return error code
 */
uint8_t I2CDevice::readBytesFromReg(byte regadd, unsigned int count,
                                    byte* const values) {
  uint8_t error_code = 0;
  size_t bytes_recieved = 0;
  wire_->beginTransmission(address_);
  wire_->write(regadd);
  error_code = wire_->endTransmission(false);
  bytes_recieved = wire_->requestFrom(address_, count, true);
  if (bytes_recieved != count) {
    error_code += 6;
  }
  for (int i = 0; i < count; i++) {
    values[i] = wire_->read();
  }
  return error_code;
}

/**
 * @brief Read a byte from a register location
 * @param regadd register address
 * @param error_code pointer to the error code
 * @return byte read from the register
 */
byte I2CDevice::readByteFromReg(byte regadd, uint8_t* error_code) {
  byte byte = 0;

  if (error_code != nullptr) {
    *error_code = readBytesFromReg(regadd, 1, &byte);
  } else {
    readBytesFromReg(regadd, 1, &byte);
  }
  return byte;
}

/**
 * @brief Read bits from a register location
 * @param regadd register address
 * @param bitmask bit mask to apply to the read value
 * @param error_code pointer to the error code
 * @return byte read from the register

*/
byte I2CDevice::readBitsFromReg(byte regadd, byte bitmask,
                                uint8_t* error_code) {
  int value;
  value = (readByteFromReg(regadd, error_code) & bitmask);
  return value;
}

/**
 * @brief Read short ints (16 bits) from a register location
 * @param regadd register address
 * @param count number of short ints to read
 * @param values pointer to the array of short ints to store the read values
 * @param msb_first true if the most significant byte is first in the register
 */
uint8_t I2CDevice::readShortIntsFromReg(byte regadd, unsigned int count,
                                        short int* values, bool msb_first) {
  uint8_t error_code = 0;
  byte Bytes[2 * count];
  error_code = readBytesFromReg(regadd, 2 * count, Bytes);
  for (int i = 0; i < count; i++) {
    if (msb_first)
      values[i] = ((Bytes[(2 * i)] << 8) + Bytes[(2 * i) + 1]);
    else
      values[i] = ((Bytes[(2 * i) + 1] << 8) + Bytes[(2 * i)]);
  }
  return error_code;
}

/**
 * @brief Read a short int (16 bits) from a register location
 * @param regadd register address
 * @param msb_first true if the most significant byte is first in the register
 * @param error_code pointer to the error code
 * @return short int read from the register
 */
short int I2CDevice::readShortIntFromReg(byte regadd, bool msb_first,
                                         uint8_t* error_code) {
  short int short_int;
  if (error_code != nullptr) {
    *error_code = readShortIntsFromReg(regadd, 1, &short_int, msb_first);
  } else {
    readShortIntsFromReg(regadd, 1, &short_int, msb_first);
  }
  return short_int;
}

/**
 * @brief Write bytes to a register location
 * @param regadd register address
 * @param count number of bytes to write
 */
uint8_t I2CDevice::writeBytesToReg(byte regadd, unsigned int count,
                                   byte* values) {
  uint8_t error_code = 0;
  wire_->beginTransmission(address_);
  wire_->write(regadd);
  for (int i = 0; i < count; i++) {
    wire_->write(values[i]);
  }
  error_code = wire_->endTransmission(true);
  return error_code;
}

/**
 * @brief Write a byte to a register location
 * @param regadd register address
 * @param value byte to write
 * @return byte read from the register
 */
uint8_t I2CDevice::writeByteToReg(byte regadd, byte value) {
  uint8_t error_code = 0;
  error_code = writeBytesToReg(regadd, 1, &value);
  return error_code;
}

/**
 * @brief Write bits to a register location
 * @param regadd register address
 * @param bitmask bit mask to apply to the read value
 * @param value byte to write
 */
uint8_t I2CDevice::writeBitsToReg(byte regadd, byte bitmask, byte value) {
  uint8_t error_code = 0;
  value =
      ((readByteFromReg(regadd, &error_code) & (~bitmask)) | (value & bitmask));
  error_code += writeByteToReg(regadd, value);
  return;
}

}  // namespace i2c_driver
