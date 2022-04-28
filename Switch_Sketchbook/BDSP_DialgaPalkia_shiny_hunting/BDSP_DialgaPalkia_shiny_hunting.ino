/*
 * BDSP Dialga/Palkia shiny hunting
 * Palkia (7 days)
 * Dialga (15 days) 8240 resets or 9.15hrs per day of resets
 * buttons needed
 * HOME X A UP
*/

#include <EEPROM.h>

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
}

void loop() { // Start at battle so reset of the arduino will open home and restart game
  // Add 1 to the counter
  eewrite(eeread(0) + 1, 0);
  
  // Restart game
  button(HOME, T);
  delay(500);
  button(X, T);

  for (int i = 0; i <= (40000/T/2); i++){ // 40 sec to load 
    button(A, T);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  button(UP, T); // Engage

  for (int i = 0; i <= (7000/T/2); i++){ // 7 sec animation
    button(A, T);
  }

  blinke = 1;
  for (int i = 0; i <= (15000/T/2); i++){ // blink and spam first move, waiting for reset
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
