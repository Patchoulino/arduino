#include <Streaming.h>

String inString = "";    // string to hold input
int currentColor = 0;
int red, green, blue = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // send an intro:
  Serial.println("\n\nString toInt() RGB:");
  Serial.println();
  // set LED cathode pins as outputs:
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  // turn on pin 13 to power the LEDs:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  int inChar;

  // Read serial input:
  if (Serial.available() > 0) {
    inChar = Serial.read();
  }

  if (isDigit(inChar)) {
    // convert the incoming byte to a char
    // and add it to the string:
    inString += (char)inChar;
  }

  // if you get a comma, convert to a number,
  // set the appropriate color, and increment
  // the color counter:
  if (inChar == ',') {
    // do something different for each value of currentColor:
    switch (currentColor) {
      case 0:    // 0 = red
        red = inString.toInt();
        // clear the string for new input:
        inString = "";
        break;
      case 1:    // 1 = green:
        green = inString.toInt();
        // clear the string for new input:
        inString = "";
        break;
      case 2:    // 2 = blue:
        blue = inString.toInt();
        // clear the string for new input:
        inString = "";
        break;
    }
    currentColor++;
  }
  // if you get a newline, you know you've got
  // the last color, i.e. blue:
  if (inChar == '.') {
    blue = inString.toInt();

    // set the levels of the LED.
    // subtract value from 255 because a higher
    // analogWrite level means a dimmer LED, since
    // you're raising the level on the anode:
    analogWrite(9, red);
    analogWrite(10, green);
    analogWrite(11, blue);

    // print the colors:
    Serial << "Red: " << red << ", Green: " << green << ", Blue: " << blue << endl;

    // clear the string for new input:
    inString = "";
    // reset the color counter:
    currentColor = 0;
  }

}
