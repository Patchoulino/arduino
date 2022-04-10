const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("HIGH");
  digitalWrite(LED, HIGH);
  delay(1000);
  Serial.println("LOW");
  digitalWrite(LED, LOW);
  delay(1000);
}
