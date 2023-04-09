const int IN[] = {A0, A1, A2, A3, A4, A5, 8, 7};
const int OUT[] = {3, 5, 6, 9, 10, 11, 12, 13};
const int USERBTN = 2;
//const int USERLED = 13;

const int OUT2[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
const int IN2[] = {31, 37, 43, 49};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i <= 7; i++)
  {
    pinMode(IN[i], INPUT);
    pinMode(OUT[i], OUTPUT);
  }

  pinMode(USERBTN, INPUT);
 //pinMode(USERLED, OUTPUT);

  Serial.begin(9600);

  for(int i = 0; i <= 15; i++)  pinMode(OUT2[i], OUTPUT);
  for(int i = 0; i <= 3; i++)   pinMode(IN2[i], INPUT);
}

int c = 0;
int signo = 1;
int buttons[] = {0, 0, 0, 0};

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(USERBTN)) for(int i = 0; i <= 7; i++) digitalWrite(OUT[i], digitalRead(IN[7-i]));
  else                     for(int i = 0; i <= 7; i++) digitalWrite(OUT[i], LOW);

  //digitalWrite(USERLED, !digitalRead(USERBTN)); //BTN => LED
  //digitalWrite(USERLED, !digitalRead(USERLED)); //LED Blink

  digitalWrite(OUT2[15-c], !digitalRead(OUT2[15-c]));
  c = c + 1 * signo;
  if(c == 16) 
  { 
    signo = -1;
    c = 15;
  }
  if(c < 0)  
  {
    signo = 1;
    c = 0;
  }
  
  //         grn  blinkT F  yel   red  
  //semaforo(2000, 3000, 1, 1000, 3000);

  int c = bin2byte();
  Serial.print("DIP Switch : ");   Serial.print(c);  Serial.print("\t");
  //Serial.write(c);

  for(int i = 0; i <= 3; i++) buttons[i] = digitalRead(IN2[3-i]);
  Serial.print("Buttons : ");   Serial.print(buttons[0]);   Serial.print(buttons[1]);   Serial.print(buttons[2]);   Serial.print(buttons[3]);   Serial.println("");
  
  delay(100);
}

byte bin2byte(){
  int c = 0;
  for(int i = 0; i <= 7; i++)
  {
    if(digitalRead(IN[i]))  
    {
      if(i <= 1)  c = c + pow(2,i);
      else        c = c + pow(2,i) + 1;
    }
  }
  return c;
}

void semaforo(int t_green, int t_blinkT, int t_blinkF, int t_yellow, int t_red){
  int cycleIterations = (t_blinkT / 1000) * t_blinkF;
  int cycleTime = 500 / t_blinkF;
  
  digitalWrite(OUT[0], HIGH);
  delay(t_green - cycleTime);

  for(int i = 0; i <= cycleIterations; i++)
  {
    digitalWrite(OUT[0], HIGH);
    delay(cycleTime);
    digitalWrite(OUT[0], LOW);
    if(i == cycleIterations) break;
    delay(cycleTime);
  }

  digitalWrite(OUT[1], HIGH);
  delay(t_yellow);
  digitalWrite(OUT[1], LOW);
  
  digitalWrite(OUT[2], HIGH);
  delay(t_red);
  digitalWrite(OUT[2], LOW);
}
