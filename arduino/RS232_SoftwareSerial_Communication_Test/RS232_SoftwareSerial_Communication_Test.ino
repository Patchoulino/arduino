#include <SoftwareSerial.h>
SoftwareSerial mySerial(A0, A1); // RX, TX

int byte0;

void setup() 
{
  Serial.begin(115200);
  mySerial.begin(115200);
}

void loop() 
{
  if (Serial.available()) 
  {
    byte0 = Serial.read();
    mySerial.write(byte0);
  }

  if (mySerial.available())
  {
    byte0 = mySerial.read();
    Serial.write(byte0);
  }
}
