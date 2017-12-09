// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
int pushButton = 7;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(pushButton, INPUT);
}

byte x = 0;

void loop() {

  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("rbc,10.");        // sends five bytes
  Wire.endTransmission();    // stop transmitting
  delay(10000);

  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("rb,10.");        // sends five bytes
  Wire.endTransmission();    // stop transmitting
  delay(10000);

  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("1cw,50,0,0,200.");        // sends five bytes
  Wire.endTransmission();    // stop transmitting
  delay(10000);
  
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("2cw,50,0,0,200,0,200,0.");        // sends five bytes
  Wire.endTransmission();    // stop transmitting
  delay(10000);
}

