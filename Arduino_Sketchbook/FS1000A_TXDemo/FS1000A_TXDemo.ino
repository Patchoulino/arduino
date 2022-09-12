/*
  Example for different sending methods
  
  http://code.google.com/p/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
}

void loop() {

  if(Serial.available())
  {
    int x = Serial.read();

    Serial.print("Sending: ");
    Serial.write(x);  //letter
    Serial.print("|");
    Serial.print(x);  //DEC
    Serial.println("");

    mySwitch.send(x, 24);
  }
  
  delay(2);
}
