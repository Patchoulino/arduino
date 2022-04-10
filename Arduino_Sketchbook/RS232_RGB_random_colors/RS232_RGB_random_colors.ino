#include <Streaming.h>

byte red = 85;
byte green = 170;
byte blue = 255;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
}

void loop() {
    delay(1);
    red++;
    green++;
    blue++;
    analogWrite(9, red);
    analogWrite(10, green);
    analogWrite(11, blue);

    // print the colors:
    Serial << "Red: " << red << ", Green: " << green << ", Blue: " << blue << endl;
}
