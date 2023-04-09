/*
 * FRLG Arduino assisted FlowTimer
 */
#include <Streaming.h>

// Bootleg variables
const boolean bootleg = 0;
const int bootleg_loop = 8; // 8 FR | 9 LG
// Arduino variables
String inString1 = "";  // string to hold input
String inString2 = "";  // string to hold input
boolean shift = 0;
int last_char = 0;
int new_char = 0;
boolean serial_monitor = 0;
// Timing variables
const byte T = 100;
unsigned long timer_frame = 0;
unsigned long timer_seed = 0;
unsigned long offset_btn = 0;
unsigned int offset = 0;
// Game variables
int pkmn_select = 1;
// Button variables
const byte POWER = 2;
const byte START = 5;
const byte SELECT = 3;
const byte A = 11;
const byte B = 10;
const byte UP = 4;
const byte DOWN = 7;
const byte LEFT = 6;
const byte RIGHT = 8;
const byte L = 9;
const byte R = 12;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  for (int i = 2; i <= 13; i++)  pinMode(i, OUTPUT);
  for (int i = 3; i <= 13; i++)  digitalWrite(i, HIGH);
  digitalWrite(POWER, LOW);
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
    else  
    {
      switch (inChar) {
        case '/':
          shift++;
          break;
        case 'Z':
          digitalWrite(POWER, !digitalRead(POWER));
          break;
        case 'f':
          button(A, T, T);
          break;
        case 'r':
          button(B, T, T);
          break;
        case 'w':
          button(UP, T, T);
          break;
        case 's':
          button(DOWN, T, T);
          break;
        case 'a':
          button(LEFT, T, T);
          break;
        case 'd':
          button(RIGHT, T, T);
          break;
        case 'q':
          button(L, T, T);
          break;
        case 'e':
          button(R, T, T);
          break;
        case 'c':
          button(START, T, T);
          break;
        case 'x':
          button(SELECT, T, T);
          break;
        case '\n':
          //serial_monitor = 1;
          if (isDigit(last_char)) {
            timer_update();
            pkmn_select = serial_input();
          }
          break;
        case '!':
          frlg_rng_starter();
          break;
        case '@':
          frlg_gamecorner(pkmn_select);  // 1 Abra | 2 Clef | 3 Dratini | 4 Scy | 5 Pory
          break;
        case '#':
          frlg_sweet_scent();
          break;
        case ',':
          frlg_new_save();
          name_patch();
          break;
        case '<':
          frlg_new_save();
          name_pau();
          break;
        case '.':
          frlg_pid_sid();
          break;
      }
    }
    last_char = inChar;
  }
}

void clear_variables() { 
  inString1 = "";
  inString2 = "";
  shift = 0;
}

void timer_update() {
  timer_frame = inString1.toInt();
  timer_seed = inString2.toInt();
  Serial << "FRLG timer: " << timer_frame << "/" << timer_seed << endl;
  clear_variables();
}

void poweron_sequence() {
  digitalWrite(POWER, HIGH);
  delay(1000);
  digitalWrite(POWER, LOW);
  delay(100);
  digitalWrite(POWER, HIGH);
  offset = 469;
  if (bootleg) {
    switch (bootleg_loop) {
      case 8: // FR
        offset = 101;
        break;
      case 9: // LG
        timer_seed = timer_seed + 570;  // should be +569 but not working
        offset = 1;
        break;
    }
  }
  delay(timer_seed - offset);
  offset_btn = 0;
  button(A, 3500, 200);
  button(A, T, T);
  if (bootleg) for (int i = 1; i <= bootleg_loop; i++)  button(A, T, T);
  for (int i = 1; i <= 17; i++)  button(B, T, T); // 4 Sec
}

void frlg_rng_starter() {
  poweron_sequence();
  for (int i = 1; i <= 15; i++)  button(A, T, T); // 3 Sec
  //long offset_btn = 10900; // Advance should be higher than 654, 750 for bootleg
  // when already powered off it hits 2 frames late so bootleg is 67 when looping and 33.6 otherwise
  if (bootleg)  offset = 34;
  else          offset = 66;
  delay(timer_frame - timer_seed - offset_btn + offset);
  button(A, T, T);
  for (int i = 1; i <= 65; i++)  button(B, T, T); // 13 Sec
  button(START, T, T);
  delay(300);
  for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
  delay(2000);
  button(RIGHT, T, T);
  delay(2000);
}

void frlg_gamecorner(int select) {
  poweron_sequence();
  for (int i = 1; i <= 7; i++)  button(A, T, T); 
  for (int i = 1; i <= select; i++)  button(DOWN, T, T);
  for (int i = 1; i <= 2; i++)  button(A, T, T);
  //long offset_btn = 9700; // Advance should be higher than 582
  if (bootleg)  offset = 34;
  else          offset = 66;
  delay(timer_frame - timer_seed - offset_btn + offset);
  button(A, T, T);
  for (int i = 1; i <= 20; i++)  button(B, T, T); // 4 Sec
  button(START, T, T);
  button(DOWN, T, T);
  delay(300);
  for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
  for (int i = 1; i <= 13; i++)  button(DOWN, T, T);
  delay(2000);
  button(RIGHT, T, T);
  delay(2000);
}

void frlg_sweet_scent() {
  poweron_sequence();
  button(START, T, T);
  button(DOWN, T, T);
  button(A, T, T);
  delay(1000);
  button(DOWN, T, T);
  button(A, T, T);
  button(DOWN, T, T);
  
  if (bootleg)  offset = 34;
  else          offset = 66;
  delay(timer_frame - timer_seed - offset_btn + offset - 5537);
  button(A, T, T);
}

int serial_input() {
  Serial << "FRLG selected: ";
  while (Serial.available() == 0) delay(100);
  int input_char2 = Serial.read() - '0';
  Serial << input_char2 << endl;
  return input_char2;
}

void frlg_pid_sid() {
   /*
    * Tools > Researcher
    * TID DEC to HEX, use as seed
    * Custom1 16Bit High / 1
    * Initial Advances 1147
    * Max Advances 5
    * Generate
    */
   int flatms = 15068;  //1149 - 1150
   //int flatms = 15922;  //1200
   offset_btn = 0;
   for (int i = 1; i <= 33; i++) button(A, T, T); // 6.6 Sec
   button(DOWN, T, T);
   for (int i = 1; i <= 24; i++) button(A, T, T); // 4.8 Sec
   delay(flatms - offset_btn + 33);
   button(A, T, T);
   for (int i = 1; i <= 35; i++) button(B, T, T);
   button(START, T, T);
   button(DOWN, T, T);
   button(A, T, T);
}

void frlg_new_save() {
  button(POWER, T, T);
  for (int i = 1; i <= 57; i++)  button(A, T, T); // 11.4 Sec
  if (bootleg) for (int i = 1; i <= bootleg_loop; i++)  button(A, T, T);
  button(DOWN, T, T);
  for (int i = 1; i <= 117; i++) button(A, T, T); // 23.4 Sec
  delay(200);
  button(DOWN, T, T); // GIRL
  for (int i = 1; i <= 15; i++)  button(A, T, T); // 3 Sec
}

void name_patch() {
  for (int i = 1; i <= 2; i++)  button(DOWN, T, T);
  for (int i = 1; i <= 3; i++)  button(RIGHT, T, T);
  button(A, T, T);  // P
  button(SELECT, T, T); // lowercase
  delay(500);
  for (int i = 1; i <= 3; i++)  button(LEFT, T, T);
  for (int i = 1; i <= 2; i++)  button(UP, T, T);
  button(A, T, T);  // a
  for (int i = 1; i <= 3; i++)  button(DOWN, T, T);
  button(A, T, T);  // t
  for (int i = 1; i <= 3; i++)  button(UP, T, T);
  for (int i = 1; i <= 2; i++)  button(RIGHT, T, T);
  button(A, T, T);  // c
  button(DOWN, T, T);
  button(LEFT, T, T);
  button(A, T, T);  // h
  button(START, T, T);
}

void name_pau() {
  for (int i = 1; i <= 2; i++)  button(DOWN, T, T);
  for (int i = 1; i <= 3; i++)  button(RIGHT, T, T);
  button(A, T, T);  // P
  button(SELECT, T, T); // lowercase
  delay(500);
  for (int i = 1; i <= 3; i++)  button(LEFT, T, T);
  for (int i = 1; i <= 2; i++)  button(UP, T, T);
  button(A, T, T);  // a
  for (int i = 1; i <= 3; i++)  button(DOWN, T, T);
  button(RIGHT, T, T);
  button(A, T, T);  // u
  button(START, T, T);
}

void button(int btn, int timing_on, int timing_off) {
  if (serial_monitor) Serial << "Button [" << btn << "]: on " << timing_on << endl;
  digitalWrite(btn, LOW);
  delay(timing_on);
  if (serial_monitor) Serial << "Button [" << btn << "]: off " << timing_off << endl;
  digitalWrite(btn, HIGH);
  delay(timing_off);
  offset_btn = offset_btn + timing_on + timing_off;
}
