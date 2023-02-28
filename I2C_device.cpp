#include "I2C_device.h"
#include <Arduino.h>
TwoWire* wireObj;
//Constructor for I2C Device
I2CDevice::I2CDevice(byte address, TwoWire* preferred_wire = &Wire){
    
    setupDevice(address,preferred_wire);
    if(!checkConnection()){
        Serial.println(" error getting Data! Check the address, port number and wiring ");
        delay(1000);
    }
}

//setting up device address_ and i2c port
void I2CDevice::setupDevice(byte address, TwoWire* preferred_wire){

    address_ = address;
    wireObj  = preferred_wire;
    return;
}


//Checking the validity of given information
bool I2CDevice::checkConnection(){

    byte error = 0;
    wireObj->beginTransmission(address_);
    error = wireObj->endTransmission();
    return (error == 0) ? true : false;
} 


//Reads bytes and updates in provided location
void I2CDevice::readBytesFromReg (byte regadd, unsigned int count,  byte* const values)
{
   wireObj.beginTransmission(address_);
   wireObj.write(regadd);
   wireObj.endTransmission(false);
   wireObj.requestFrom(address_,count,true);
   for (int i = 0; i < count; i++)
    {
        values[i] = wireObj.read();
    }
    break;
        
}
    


//Returns a byte read from given register
byte I2CDevice::readByteFromReg(byte regadd)
{
    byte Byte;
    readBytesFromReg(regadd,1,&Byte);
    return Byte;
}


//Returns a byte  with values of required bits read from given register
byte I2CDevice::readBitsFromReg(byte regadd,byte bitmask)
{
    int value;
    value = ( readByteFromReg( regadd) & bitmask );
    return value;

}

 //Reads an array of short ints from a reg location 
 void I2CDevice::readShortIntsFromReg( byte regadd,unsigned int count,short int* values)
{
   byte Bytes[2*count];
   readBytesFromReg(regadd,2*count,Bytes);
   for (int i = 0; i < count; i++)
   {
       values[i] = ((Bytes[ (2*i) ]<<8) + Bytes[(2*i) + 1 ]);
   }

   return;
   
} 

 //Reads an short int and returns it
 short int I2CDevice::readShortIntFromReg( byte regadd)
{
    short int short_int;
    readShortIntsFromReg(regadd,1,&short_int);

    return short_int;
} 




// write an array of bytes to a register location
void I2CDevice::writeBytesToReg(byte regadd, unsigned int count,byte* values)
{
    wireObj.beginTransmission(address_);
    wireObj.write(regadd);
    for (int i = 0;i < count; i++){
        wireObj.write(values[i]);
    }
    wireObj.endTransmission(true);
    break;
       

} 

// write a byte to a register 
void I2CDevice::writeByteToReg(byte regadd,byte  value)
{
    writeBytesToReg(regadd,1,&value);
    return;
} 



//write bits to a register
void I2CDevice::writeBitsToReg(byte regadd,byte bitmask,byte value)
{
    value = ((readByteFromReg(regadd) & (~bitmask)) | (value & bitmask));
    writeByteToReg(regadd,value);
    return;
}