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

int RGBsign = 1;
int RGB[] = {0, 0, 0};

void loop() {
  // put your main code here, to run repeatedly:

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

  int c = bin2byte();
  Serial.print("Switches: ");   Serial.print(c);  Serial.print("\t");
  //Serial.write(c);

  for(int i = 0; i <= 3; i++) buttons[i] = digitalRead(IN2[3-i]);
  Serial.print("Buttons: ");   Serial.print(buttons[0]);   Serial.print(buttons[1]);   Serial.print(buttons[2]);   Serial.print(buttons[3]);   Serial.print("\t");

  if(!digitalRead(USERBTN))  
  {
    RGBsign = RGBsign * -1;
    if(RGBsign == -1) digitalWrite(OUT[7], HIGH);
    else              digitalWrite(OUT[7], LOW);
    while(!digitalRead(USERBTN)){delay(1);}
  }

  for(int i = 0; i <= 3; i++)
  {
    if(buttons[i] == HIGH)
    {
      if(i < 3)
      {
        RGB[i] = RGB[i] + 256/4 * RGBsign;
        if(RGB[i] > 255)
        {
          RGB[i] = 255;
        }
        else
        {
          if(RGB[i] < 0)
          {
            RGB[i] = 0;
          }
        }
      }
      else
      {
        for(int j = 0; j <= 3; j++) RGB[j] = 0;
      }
      analogWrite(9,  RGB[0]);
      analogWrite(10, RGB[1]);
      analogWrite(11, RGB[2]);
      while(digitalRead(IN2[3-i])){delay(1);}
    }
  }

  Serial.print("RGB: ");  Serial.print(RGB[0]);  Serial.print("|");  Serial.print(RGB[1]);  Serial.print("|");  Serial.print(RGB[2]);  Serial.println("");
  
  delay(100);
}

byte bin2byte(){
  int c = 0;
  for(int i = 0; i <= 7; i++)
  {
    if(digitalRead(IN[i]) == HIGH)  
    {
      if(i <= 1)  c = c + pow(2,i);
      else        c = c + pow(2,i) + 1;
    }
  }
  return c;
}
