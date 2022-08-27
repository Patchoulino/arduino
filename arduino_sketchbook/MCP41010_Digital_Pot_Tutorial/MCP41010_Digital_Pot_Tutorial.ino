/*
 * MCP41010 SPI Tutorial
 * 1 = !CS => 10  SS
 * 2 = SCK => 13  SCK
 * 3 = SI  => 11  MOSI
 * 4 = VSS => Gnd
 * 5 = PA0 => Gnd
 * 6 = PW0 => A0
 * 7 = PB0 => 5V
 * 8 = VDD => 5V
 */


#include <SPI.h>  
const int CS = 10;
int PotWiperVoltage = A0;
int RawVoltage = 0;
float Voltage = 0;
 
void setup() {
  pinMode (CS, OUTPUT);   
  Serial.begin(9600);
  SPI.begin();    
}
 
void loop() {
  // move the potentiometer in one direction
  for (int level = 0; level <= 255; level++) 
  {
    MCP41010Write(level);
    delay(50);
    RawVoltage = analogRead(PotWiperVoltage);
    Voltage = (RawVoltage * 5.0 )/ 1024.0;
    Serial.print("Level = " );                      
    Serial.print(level);      
    Serial.print("\t Voltage = ");
    Serial.println(Voltage,3);  
    delay(50);
  }
  delay(2000);  // wait a couple seconds
  // Now mover potentiometer in other directions
  
  for (int level = 255; level >= 0; level--) 
  {
    MCP41010Write(level);
    delay(50);
    RawVoltage = analogRead(PotWiperVoltage);
    Voltage = (RawVoltage * 5.0 )/ 1024.0;
    Serial.print("Level = " );                      
    Serial.print(level);      
    Serial.print("\t Voltage = ");
    Serial.println(Voltage,3); 
    delay(50);
  }
   delay(2000);
}
 //255 = 4.971
 //1   = 0.024
 //0   = 0
void MCP41010Write(byte value) 
{
  // Note that the integer vale passed to this subroutine
  // is cast to a byte
  
  digitalWrite(CS,LOW);
  SPI.transfer(B00010001); // This tells the chip to set the pot
  SPI.transfer(value);     // This tells it the pot position
  digitalWrite(CS,HIGH); 
}
