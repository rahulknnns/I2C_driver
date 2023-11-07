# I2C_driver:
* Most of the I2C sensors seems to have a well established procedure to get sensor data. (i.e) The sensors provide registers, Any interaction with the sensor is performed using reading and writing to registers. This will work if the following assumptions are said to be true:
 1) reading from a register is performed using following sequence: write the register address -> issue a read request in next transaction.
 2) writing to a register is performed using following sequence: write the register address followed by the register value in the same transaction.
 3) reading or writing multiple values automatically increments the register address so multiple read/write operations can be performed in single operation.


**Note:** These conditions are met in most of the popular  I2C sensors like MPU6050, HMC5883Q, FXAS5300Q, FXOS8700Q, etc. Make sure your I2C device meets the above conditions to use this library.

## Usage:
  * Create a I2C device object and initialise with a address and preferred_wire. preferred_wire should be a pointer to Wire Object like &Wire, &Wire1, &Wire2. This is particularly useful if the microcontroller multiple I2C ports.
  * By default &Wire is chosen.
  * It is also expected to initialise the Wire object by calling Wire.begin() seperately in your code as the library doesn't do so.
  * Use the read / write functions provided by the class.
  *  Detailed API usage can be found [here](link).

