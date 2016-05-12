
#include <Wire.h>

byte port = 0x12;      //Port A (0x12) Port B (0x13)
byte address = 0x20;
byte output = 0x00;
unsigned int count = 1;

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // join i2c bus 

  //Initializes all 
  
  Wire.beginTransmission(0x20);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x20);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x21);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x21);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x24);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x24);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x25);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x25);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();



}



void loop()
{
 
  if (count > 128){
    count = 1; 
    address++;
  }
   
  Serial.println(address);
  Serial.println(port);
  //Serial.println(output);
  Serial.println(count);
  Serial.println();
    
  Wire.beginTransmission(address);
  Wire.write(port); // address port A
  Wire.write(count);  // value to send
  Wire.endTransmission();
    
  if (port == 0x12){
    port = 0x13;
  }
  else{
    port = 0x12;
    count = count * 2;
  }

  
  
  delay(500);
}
