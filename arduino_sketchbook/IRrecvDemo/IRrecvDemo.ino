/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int led = 13;
int RECV_PIN =  2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    Serial.println(results.value);

    switch(results.value)
    {
      case 16730805:
        digitalWrite(led, LOW);
        break;
      case 16738455:
        digitalWrite(led, HIGH);
        break;
    }
    
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
