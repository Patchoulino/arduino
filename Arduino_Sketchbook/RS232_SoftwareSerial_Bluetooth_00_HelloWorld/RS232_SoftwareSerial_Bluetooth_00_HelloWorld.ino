#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12); // RX, 

int byte0;

char character;
String text = "";

boolean blinking = false;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  if (Serial.available()) {
    byte0 = Serial.read();
    //mySerial.write(byte0);
    debug();
  }

  if (mySerial.available()) {
    byte0 = mySerial.read();
    //Serial.write(byte0);
    control();
  }
  
  if (blinking) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(100);
  }
}

void control(void) {
    switch(byte0) {
    case '1':
      text = "";
      while (mySerial.available()) {
        character = mySerial.read();
        text.concat(character);
      }
      Serial.println(text);
      break;
    case '2':
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      break;
    case '3':
      blinking = !blinking;
      break;
    case '4':
      mySerial.print(text);
      break;
    }
}

void debug(void) {
    switch(byte0) {
    case '1':
      text = "";
      while (Serial.available()) {
        character = Serial.read();
        text.concat(character);
      }
      mySerial.println(text);
      break;
    case '2':
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      break;
    case '3':
      blinking = !blinking;
      break;
    }
}
