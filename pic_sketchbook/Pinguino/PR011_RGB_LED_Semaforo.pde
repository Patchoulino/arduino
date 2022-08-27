const int RED = 28;
const int GRN = 27;
const int BLU = 26;

void setup() {
    // put your setup code here, to run once:
    pinMode(RED, OUTPUT);
    pinMode(GRN, OUTPUT);
    pinMode(BLU, OUTPUT);
    
    digitalWrite(RED, HIGH);
    digitalWrite(BLU, HIGH);
    delay(500);
    delay(500);
    digitalWrite(RED, LOW);
    digitalWrite(BLU, LOW);
    digitalWrite(GRN, HIGH);
    delay(500);
    digitalWrite(GRN, LOW);
}

void loop() {
    // put your main code here, to run repeatedly:
    
    int t_green = 2000;
    int t_blinkT = 2000;
    int t_blinkF = 2;
    int t_yellow = 1000;
    int t_red = 3000;
    
  long cycleIterations = (t_blinkT / 1000) * t_blinkF;
  long cycleTime = 500 / t_blinkF;
  long i;
  
  digitalWrite(GRN, HIGH);
  delay(t_green - cycleTime);

  for(i = 0; i <= cycleIterations; i++)
  {
    digitalWrite(GRN, HIGH);
    delay(cycleTime);
    digitalWrite(GRN, LOW);
    if(i == cycleIterations) break;
    delay(cycleTime);
  }

  digitalWrite(GRN, HIGH);
  digitalWrite(RED, HIGH);
  delay(t_yellow);
  digitalWrite(GRN, LOW);
  
  delay(t_red);
  digitalWrite(RED, LOW);
}

void semaforo(long t_green, long t_blinkT, int t_blinkF, long t_yellow, long t_red){
  long cycleIterations = (t_blinkT / 1000) * t_blinkF;
  long cycleTime = 500 / t_blinkF;
  long i;
  
  digitalWrite(GRN, HIGH);
  delay(t_green - cycleTime);

  for(i = 0; i <= cycleIterations; i++)
  {
    digitalWrite(GRN, HIGH);
    delay(cycleTime);
    digitalWrite(GRN, LOW);
    if(i == cycleIterations) break;
    delay(cycleTime);
  }

  digitalWrite(GRN, HIGH);
  digitalWrite(RED, HIGH);
  delay(t_yellow);
  digitalWrite(GRN, LOW);
  
  delay(t_red);
  digitalWrite(RED, LOW);
}