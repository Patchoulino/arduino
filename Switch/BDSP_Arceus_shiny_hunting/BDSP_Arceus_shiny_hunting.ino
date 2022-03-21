/*
 * BDSP Arceus shiny hunting
 * buttons needed
 * HOME X A UP
 */

const int T = 300;
const int HOME = 2;
const int X = 3;
const int A = 4;
const int UP = 5;
const int LED = 13;

void setup() {
  for (int i = 2; i <= 5; i++) { // Set all pins as outputs and 1
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() { // Start at battle with arceus so reset of the arduino will open home and restart game
  // Restart game
  button(HOME, T);
  delay(300);
  button(X, T);
  //button(A, T);
  //button(A, T);
  //button(A, T);

  for (int i = 0; i <= (40000/T/2); i++){ // 38 sec to load + 2sec for the buttons above
    button(A, T);
  }

  digitalWrite(LED, HIGH);
  button(UP, T); // Walk to god

  for (int i = 0; i <= (30000/T/2); i++){ // 30 sec Arceus animation
    button(A, T);
  }

  while (true) { // Light the led waiting for a reset
    button(LED, T);
  }
  
}

void button(int btn, int timing) {
  digitalWrite(btn, LOW);
  delay(timing);
  digitalWrite(btn, HIGH);
  delay(timing);
}
