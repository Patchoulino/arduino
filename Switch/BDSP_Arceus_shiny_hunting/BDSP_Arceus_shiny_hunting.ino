/*
 * BDSP Arceus shiny hunting
 * buttons needed
 * HOME X A UP
 */

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

void loop() { // Start at battle with arceus so reset of the arduino will open home and restart game
  // Restart game
  button(HOME, T);
  delay(500);
  button(X, T);
  //button(A, T);
  //button(A, T);
  //button(A, T);

  for (int i = 0; i <= (40000/T/2); i++){ // 40 sec to load 
    button(A, T);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  button(UP, T); // Walk to god

  for (int i = 0; i <= (17500/T/2); i++){ // 17.5 sec Arceus animation
    button(A, T);
  }

  blinke = 1;
  for (int i = 0; i <= (20000/T/2); i++){ // blink and spam first move, waiting for reset
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
