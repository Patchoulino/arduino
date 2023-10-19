/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogOutPin = 3; // Analog output pin that the LED is attached to

int outputValue = 0;        // value output to the PWM (analog out)
int x = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the serial monitor:
  Serial.print("Output = ");
  Serial.println(outputValue);

  // wait 1 milliseconds before the next loop
  delay(1);
  
  if(x == 0)
  {
    outputValue++;
    if(outputValue == 100) x = 1;
  }
  else
  {
    outputValue--;
    if(outputValue == 0) x = 0;
  }
}
