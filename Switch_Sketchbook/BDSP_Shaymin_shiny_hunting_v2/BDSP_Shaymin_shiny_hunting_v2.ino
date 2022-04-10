/*
 * BDSP Shaymin shiny hunting no game reset
 * buttons needed
 * A UP DOWN B
 */

const int T = 300;
int blinke = 0;
//const int HOME = 2;
//const int X = 3;
const int A = 4;
const int UP = 5;
const int DOWN = 6;
const int B = 7;

void setup() {
  for (int i = 2; i <= 7; i++) { // Set all pins as outputs and 1
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() { // Start in front of spawn
  int running_time = 3000;  // Run outside to reset encounter
  digitalWrite(DOWN, LOW);
  digitalWrite(B, LOW);
  delay(running_time);
  digitalWrite(DOWN, HIGH);
  digitalWrite(UP, LOW);  // Run back
  delay(running_time-100);
  digitalWrite(UP, HIGH);
  digitalWrite(B, HIGH);  

  digitalWrite(LED_BUILTIN, HIGH);
  button(A, T); // Engage

  for (int i = 0; i <= (10000/T/2); i++){ // animation
    button(A, T);
  }

  blinke = 1;
  for (int i = 0; i <= (12000/T/2); i++){ // blink and spam B
    button(B, T);
  }
  blinke = 0;
  digitalWrite(LED_BUILTIN, LOW);

  button(UP, T); // Run away
  button(A, T);
  delay(3800);
  button(B, T); // Clear Shaymin message
}

void button(int btn, int timing) {
  digitalWrite(btn, LOW);
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
  digitalWrite(btn, HIGH);
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
}
