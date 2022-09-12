/*
 * BDSP box item cloning
 * buttons needed
 * A B X R DOWN LEFT RIGHT
 */

const int T = 300;
const int A = 2;
const int B = 3;
const int X = 4;
const int DOWN = 5;
const int LEFT = 6;
const int RIGHT = 7;
const int R = 8;

void setup() {
  for (int i = 2; i <= 8; i++) { // Set all pins as outputs and 1
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() { // Start at box first menu, have menu first selection be pokemon/party
  // Mouseover Check Summary
  button(A, T);
  button(DOWN, T);

  // Second menu, item ready
  button(X, T);
  button(A, T);
  delay(800);
  button(R, T);
  delay(1200);
  button(X, T);

  int orientation = 1;  // 1 = Right
  for (int y = 0; y <= 4; y++) {
    for (int x = 0; x <= 5; x++) { 
      if (x > 0) {
        // Shift L/R
        if (orientation == 1) button(RIGHT, T-100);
        else  button(LEFT, T-100);
      }
      for (int z = 0; z <= 4; z++) { // Pick item
        if (z == 4) delay(200); // You placed x item takes longer
        if (z == 1) button(DOWN, T);
        else button(A, T);
      }
    }
    if (y < 4) {
      // Change orentiation and shift down
      if (orientation == 1) orientation = 0;
      else  orientation = 1;
      button(DOWN, T);
    }
  }

  // Exit and check summary to reset items
  for (int x = 0; x <=4; x++) {
    if (x == 3) {
      button(A, 500);
      delay(500);
    }
    else  button(B, 700);
  }
  delay(1200);
}

void button(int btn, int timing) {
  digitalWrite(btn, LOW);
  delay(timing);
  digitalWrite(btn, HIGH);
  delay(timing);
}
