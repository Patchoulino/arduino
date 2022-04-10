const int red = 3;
const int yel = 6;

void setup() {
  pinMode(red,OUTPUT);
  pinMode(yel,OUTPUT);
}

void loop() {
  analogWrite(red,random(120)+135);
  analogWrite(yel,random(120)+135);
  delay(random(100));
}
