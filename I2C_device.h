#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H
#include <Arduino.h>
#include <Wire.h>

 class I2CDevice 
{
    protected:
    byte address_;
    TwoWire wire_;

   
    public:
    //Initializer Functions
    I2CDevice() =default;
    I2CDevice(byte address,int port_no = 0, int frequency = 400000);
    void setupDevice(byte address, int port_no, int frequency );
    bool checkConnection();
    
    //read Functions
    int readBytesFromReg (byte regadd, int count, byte* values);
    byte readByteFromReg (byte regadd);
    byte readBitsFromReg(byte regadd,byte bitmask);
    void readShortIntsFromReg (byte regadd,int count, short int* values);
    short int  readShortIntFromReg (byte regadd);
    
    //write Functions
    int  writeBytesToReg(byte regadd,int count,byte* value);
    void writeByteToReg(byte regadd,byte value);
    void writeBitsToReg(byte regadd, byte bitmask,byte value);

};
#endif