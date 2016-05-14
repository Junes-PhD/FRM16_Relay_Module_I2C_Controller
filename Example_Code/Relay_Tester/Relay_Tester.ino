
#include <Wire.h>


byte port = 0x13;      //Port A (0x12) Port B (0x13)
byte address = B00100000;  //B00100A2A1A0  sets address with A jumpers
byte output = 0x00;
boolean resetstate = HIGH;
int resetpin = 8;          //Reset active low
unsigned int count = 1;
unsigned int relay = 0;

void setup()
{  
  pinMode(resetpin, OUTPUT);
  
  Serial.begin(9600);
  Wire.begin(); // join i2c bus 
  
  rst();       //Initializes Expander Outputs
  
}

void loop()
{
 // Change I2C address when done cycling through all of the outputs
  if (count > 128){
    count = 1; 
    relay = 0;
    delay(1000);
    address++;
    rst();   
  }
  
  Serial.print("Address: "); 
  if ((address & B110) == 0){          //formating output
    Serial.print("00");
  } 
  else if((address & B100) == 0){
    Serial.print("0"); 
  }
  
  Serial.println(address & B111, BIN);  //Bitwise AND to just show A2,A1,A0 values
  
  Wire.beginTransmission(address);
  Wire.write(port); // address port A
  Wire.write(count);  // value to send
  Wire.endTransmission();
  
  
 
    
  if (port == 0x13){
    Serial.print("GPIO: B"); 
    Serial.println(relay);    
    Serial.print("Relay:");    //B side relay
    Serial.println(relay);
    port = 0x12;
  }
  else{
    Serial.print("GPIO: A"); 
    Serial.println(relay);
    Serial.print("Relay:");
    Serial.println(relay + 8);  //A side offset0
    port = 0x13;
    count = count * 2;
    relay++;
  }

  Serial.println();
  
  delay(500);
  
}

void rst (void){
    
    Serial.print("Starting Address:");  //IC address in decimal
    Serial.println(address & B111);
    Serial.println();
    
    //reset chip
    digitalWrite(resetpin, LOW);
    digitalWrite(resetpin, HIGH);
    
    //Initializes Expander Outputs which current target IC
    Wire.beginTransmission(address);
    Wire.write(0x00); // IODIRA register
    Wire.write(0x00); // set all of port A to outputs
    Wire.endTransmission();
    
    Wire.beginTransmission(address);
    Wire.write(0x01); // IODIRB register
    Wire.write(0x00); // set all of port B to outputs
    Wire.endTransmission();
}
