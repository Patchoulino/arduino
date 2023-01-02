/*
 * FRLG Arduino assisted FlowTimer
 */
#include <Streaming.h>

String inString1 = "";  // string to hold input
String inString2 = "";  // string to hold input
boolean shift = 0;
const byte T = 100;
const byte POWER = 2;
const byte START = A1;
const byte A = A3;
const byte B = A5;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  for (int i = 2; i <= 5; i++)  pinMode(i, OUTPUT);
  for (int i = 3; i <= 5; i++)  digitalWrite(i, HIGH);
  digitalWrite(POWER, LOW);

  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      if ( shift == 0 ) inString1 += (char)inChar;
      else              inString2 += (char)inChar;
    }
    else  shift++;
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      unsigned long timer1 = inString1.toInt();
      unsigned long timer2 = inString2.toInt();
      //unsigned long frame = ((1000 * timer1) / 60UL);
      Serial << "Timer 1: " << timer1 << "; String 1: " << inString1 << endl;
      Serial << "Timer 2: " << timer2 << "; String 2: " << inString2 << endl;
      // clear the string for new input:
      inString1 = "";
      inString2 = "";
      shift = 0;

      digitalWrite(POWER, HIGH);
      //delay(timer2 - 519);
      delay(timer2);
      button(A, 3500, 200);
      button(A, T, T);
      for (int i = 1; i <= 20; i++)  button(B, T, T); // 4 Sec
      for (int i = 1; i <= 15; i++)  button(A, T, T); // 3 Sec
      long offset = 10900;
      delay(timer1 - timer2 - offset + 50);
      //delay(timer1 - timer2 - offset);
      //delay(frame - offset); // timer1 being the frame
      button(A, T, T);
      for (int i = 1; i <= 55; i++)  button(B, T, T); // 11 Sec
      button(START, T, T);
      delay(300);
      for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
    }
  }
}

void button(int btn, int timing_on, int timing_off) {
  digitalWrite(btn, LOW);
  delay(timing_on);
  digitalWrite(btn, HIGH);
  delay(timing_off);
}
