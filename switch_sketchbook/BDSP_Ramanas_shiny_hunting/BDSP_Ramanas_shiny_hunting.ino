/*
 * BDSP Ramanas Park shiny hunting
 * buttons needed
 * HOME X A UP
 * Latios 2022-05-28 - 18261 as of 9/01 and gaveup
 * Latias 
*/

#include <EEPROM.h>
#include <Streaming.h>

const int T = 300;
int blinke = 0;
const int HOME = 2;
const int X = 3;
const int A = 4;
const int UP = 5;

void setup() {
  for (int i = 2; i <= 5; i++) { // Set all pins as outputs and 1
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
}

void loop() { // Start at battle so reset of the arduino will open home and restart game
  // Add 1 to the counter
  eewrite(eeread(0) + 1, 0);
  Serial << "Int: " << eeread(0) << " byte(0): " << EEPROM.read(0) << " byte(1): " << EEPROM.read(1) << endl;
  
  // Restart game
  button(HOME, T);
  delay(500);
  button(X, T);

  for (int i = 0; i <= (41000/T/2); i++){ // 40 sec to load 
    button(A, T);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  button(UP, T); // Engage

  for (int i = 0; i <= (9000/T/2); i++){ // animation
    button(A, T);
  }

  blinke = 1;
  for (int i = 0; i <= (9500/T/2); i++){ // blink and spam first move, waiting for reset
    button(A, T);
  }
  blinke = 0;
  digitalWrite(LED_BUILTIN, LOW);
}

void button(int btn, int timing) {
  digitalWrite(btn, LOW);
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
  digitalWrite(btn, HIGH);
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
}

void eewrite(unsigned int value, int address) {
  EEPROM.write(address, value & 0xFF);
  EEPROM.write(address + 1, value >> 8);
}

unsigned int eeread(int address) {
  return  (EEPROM.read(address + 1) << 8) + EEPROM.read(address);
}
