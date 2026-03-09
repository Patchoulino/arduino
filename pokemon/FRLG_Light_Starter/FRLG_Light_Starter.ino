/*
 * FRLG Light sensor Arduino nano
 */
#include <Streaming.h>
#include <EEPROM.h>

// Timing variables
const byte T = 100;
double timer_frame_ms_math = 0;
unsigned long timer_frame_ms = 0;
unsigned long timer_frame = 0;
unsigned long timer_seed = 0;
unsigned long offset_btn = 0;
int offset = 0;
// Game variables
int pkmn_select = 1;
// Button variables
const byte HOME = 2;
const byte UP = 3;
const byte RIGHT = 4;
const byte DOWN = 5;
const byte LEFT = 6;
const byte B = 7;
const byte A = 8;
const byte START = 9;
const byte X = 9;
const byte SELECT = 10;
const byte Y = 10;
const byte R = 11;
const byte L = 12;

// Analog
int sensorValue = 0;
const int analogInPin = A3;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  for (int i = 2; i <= 13; i++)  pinMode(i, OUTPUT);
  for (int i = 2; i <= 13; i++)  digitalWrite(i, HIGH);
  //digitalWrite(POWER, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  starter_sh();
}

void starter_sh() {
  int previous_value = 0;
  while (true){
    for (int i = 1; i <= 35; i++)  button(A, T, T); // 7 Sec  // Start game
    for (int i = 1; i <= 15; i++)  button(B, T, T); // 3 Sec  // Skip Recap
    for (int i = 1; i <= 16; i++)  button(A, T, T); // 3 Sec  // Select Starter
    for (int i = 1; i <= 60; i++)  button(B, T, T); // 12 Sec // Spam B while rival grabs starter
    button(START, T, T);  // check pokemon
    delay(300);
    for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
    delay(1000);
    //delay(1000);
    //button(RIGHT, T, T);
    //delay(5000);
    sensorValue = analogRead(analogInPin);
    Serial << "Counter: " << eeread(0) << " byte(0): " << EEPROM.read(0) << " byte(1): " << EEPROM.read(1) << " | Analog Read: " << sensorValue << " | Previous Value: " << previous_value << endl;
    if (sensorValue < (previous_value - 5)) {  // Shiny found! ( diff is very small, 10 out of the 1024/5V scale)
      while (true) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(100);
      }
    }
    previous_value = sensorValue;
    eewrite(eeread(0) + 1, 0);
    restart_game_fast();
  }
}

void restart_game_fast() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(X, LOW);
  digitalWrite(Y, LOW);
  delay(T);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(X, HIGH);
  digitalWrite(Y, HIGH);
  delay(T);
}

void button(int btn, int timing_on, int timing_off) {
  digitalWrite(btn, LOW);
  delay(timing_on);
  digitalWrite(btn, HIGH);
  delay(timing_off);
}

void eewrite(unsigned int value, int address) {
  EEPROM.write(address, value & 0xFF);
  EEPROM.write(address + 1, value >> 8);
}

unsigned int eeread(int address) {
  return  (EEPROM.read(address + 1) << 8) + EEPROM.read(address);
}