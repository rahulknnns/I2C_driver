#include "I2C_device.hpp"

/**
 * @brief Construct a new I2CDevice::I2CDevice object
 * @param address I2C address of the device 0 - 127
 * @param preferred_wire I2C port to use e.g. Wire, Wire1, Wire2
*/
I2CDevice::I2CDevice(byte address, TwoWire* preferred_wire ){
    
    setupDevice(address,preferred_wire);
    
}

/**
 * @brief Set up the parameters I2C device
 * @param address I2C address of the device 0 - 127
 * @param preferred_wire I2C port to use e.g. Wire, Wire1, Wire2
*/
void I2CDevice::setupDevice(byte address, TwoWire* preferred_wire){

    address_ = address;
    wire_  = preferred_wire;
    return;
}


/**
 * @brief Check if the device is connected
 * @return true if connected
 * @return false if not connected

*/
bool I2CDevice::checkConnection(){

    byte error = 0;
    wire_->beginTransmission(address_);
    error = wire_->endTransmission();
    return (error == 0) ? true : false;
} 

void I2CDevice::begin(){
    if(!checkConnection()){
        Serial.println(" error getting Data! Check the address, port number and wiring ");
        Serial.println(" I2C address: " + String(address));
        delay(1000);
    }
}
/**
 * @brief Read bytes from a register location
 * @param regadd register address
 * @param count number of bytes to read
 * @param values pointer to the array of bytes to store the read values
*/
void I2CDevice::readBytesFromReg (byte regadd, unsigned int count,  byte* const values)
{
   wire_->beginTransmission(address_);
   wire_->write(regadd);
   wire_->endTransmission(false);
   wire_->requestFrom(address_,count,true);
   for (int i = 0; i < count; i++)
    {
        values[i] = wire_->read();
    }        
}
    

/**
 * @brief Read a byte from a register location
 * @param regadd register address
 * @return byte read from the register
*/
byte I2CDevice::readByteFromReg(byte regadd)
{
    byte Byte;
    readBytesFromReg(regadd,1,&Byte);
    return Byte;
}


/**
 * @brief Read bits from a register location
 * @param regadd register address
 * @param bitmask bit mask to apply to the read value
 * @return byte read from the register

*/
byte I2CDevice::readBitsFromReg(byte regadd,byte bitmask)
{
    int value;
    value = ( readByteFromReg( regadd) & bitmask );
    return value;

}

/**
 * @brief Read short ints (16 bits) from a register location
 * @param regadd register address
 * @param count number of short ints to read
 * @param values pointer to the array of short ints to store the read values
 * @param msb_first true if the most significant byte is first in the register
*/
void I2CDevice::readShortIntsFromReg( byte regadd,unsigned int count,short int* values,bool msb_first)
{
   byte Bytes[2*count];
   readBytesFromReg(regadd,2*count,Bytes);
   for (int i = 0; i < count; i++)
   {
         if(msb_first)
            values[i] = ((Bytes[ (2*i) ]<<8) + Bytes[(2*i) + 1 ]);
         else
            values[i] = ((Bytes[ (2*i) + 1 ]<<8) + Bytes[(2*i) ]);
   }
   return;
   
} 

/**
 * @brief Read a short int (16 bits) from a register location
 * @param regadd register address
 * @return short int read from the register
*/
short int I2CDevice::readShortIntFromReg( byte regadd,bool msb_first)
{
    short int short_int;
    readShortIntsFromReg(regadd,1,&short_int,msb_first);

    return short_int;
} 



/**
 * @brief Write bytes to a register location
 * @param regadd register address
 * @param count number of bytes to write
*/
void I2CDevice::writeBytesToReg(byte regadd, unsigned int count,byte* values)
{
    wire_->beginTransmission(address_);
    wire_->write(regadd);
    for (int i = 0;i < count; i++){
        wire_->write(values[i]);
    }
    wire_->endTransmission(true);       

} 

/**
 * @brief Write a byte to a register location
 * @param regadd register address
 * @param value byte to write
 * @return byte read from the register
*/
void I2CDevice::writeByteToReg(byte regadd,byte  value)
{
    writeBytesToReg(regadd,1,&value);
    return;
} 


/**
 * @brief Write bits to a register location
 * @param regadd register address
 * @param bitmask bit mask to apply to the read value
 * @param value byte to write
*/
void I2CDevice::writeBitsToReg(byte regadd,byte bitmask,byte value)
{
    value = ((readByteFromReg(regadd) & (~bitmask)) | (value & bitmask));
    writeByteToReg(regadd,value);
    return;
}
