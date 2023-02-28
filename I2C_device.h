#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H
#include <Arduino.h>
#include <Wire.h>

 class I2CDevice 
{
    protected:
        byte address_; 
   
    public:
    //Initializer Functions
        I2CDevice() =default;
        I2CDevice(byte address, TwoWire* preferred_wire = &Wire);
        
        
        //read Functions
        void readBytesFromReg (byte regadd, unsigned int count, byte* values);
        byte readByteFromReg (byte regadd);
        byte readBitsFromReg(byte regadd,byte bitmask);
        void readShortIntsFromReg (byte regadd, unsigned int count, short int* values);
        short int  readShortIntFromReg (byte regadd);
        
        //write Functions
        void  writeBytesToReg(byte regadd,unsigned int count,byte* value);
        void  writeByteToReg(byte regadd,byte value);
        void  writeBitsToReg(byte regadd, byte bitmask,byte value);

    protected:
        void setupDevice(byte address,unsigned int port_no );
        bool checkConnection();

};
#endif