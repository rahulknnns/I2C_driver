#include "I2C_device.h"
#include <Arduino.h>
#include <stdlib.h>

//Constructor for I2C Device
I2CDevice::I2CDevice(byte address, int port_no = 0, int frequency = 400000){
    
    setupDevice(address,port_no);
    while (!checkConnection()){
        Serial.println(" error getting Data! Check the address, port number and wiring ");
        delay(1000);
    }
}

//setting up device address_ and i2c port
void I2CDevice::setupDevice(byte address, int port_no, int frequency ){

    address_ = address;
    switch (port_no){

    case 0:
        wire_ = Wire;
        break;
    case 1:
        wire_ = Wire1;
        break;
    case 2:
        wire_ = Wire2;
        break;
    default:
       Serial.println("Wrong port selected! Teensy has only 3 ports.");
        break;
    }
    wire_.begin();
    wire_.setClock(frequency);
    return;
}


//Checking the validity of given information
bool I2CDevice::checkConnection(){

    byte error = 0;

    wire_.begin();
    wire_.beginTransmission(address_);
    error = wire_.endTransmission();
        
    
    return (error == 0) ? true : false;
} 


//Reads bytes and updates in provided location
int I2CDevice::readBytesFromReg (byte regadd, int count,  byte* const values)
{
    
    wire_.beginTransmission(address_);
    wire_.write(regadd);
    while (wire_.endTransmission(false)){

        Serial.println("error reading from device, retrying ....");
        delay(1000);
    }
         
    count = wire_.requestFrom(address_,count);
    for (int i = 0; i < count; i++)
    {
        values[i] = wire_.read();
    }
    return;
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
 void I2CDevice::readShortIntsFromReg( byte regadd,int count,short int* values)
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
int I2CDevice::writeBytesToReg(byte regadd,int count,byte* values)
{

    wire_.begin();
    wire_.beginTransmission(this->address_);
    wire_.write(regadd);
    for (int i = 0;i < count; i++)
    {
        wire_.write(values[i]);
    }
    return wire_.endTransmission(true);
    

} 

// write a byte to a register 
int I2CDevice::writeByteToReg(byte regadd,byte  value)
{

    return writeBytesToReg(regadd,1,&value);
} 



//write bits to a register
int I2CDevice::writeBitsToReg(byte regadd,byte bitmask,byte value)
{
    value = ((readByteFromReg(regadd) & (~bitmask)) | (value & bitmask));
    
    return writeByteToReg(regadd,value);
}