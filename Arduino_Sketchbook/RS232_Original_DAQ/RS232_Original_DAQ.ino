const int input0 = A0;
const int input1 = A1;
const int input2 = A2;
const int input3 = A3;
const int input4 = A4;
const int input5 = A5;
const int input6 = 2;
const int input7 = 3;

const int output0 = 4;
const int output1 = 5;
const int output2 = 6;
const int output3 = 7;
const int output4 = 8;
const int output5 = 9;
const int output6 = 10;
const int output7 = 13;

void setup() 
{
  pinMode(input0, INPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(input3, INPUT);
  pinMode(input4, INPUT);
  pinMode(input5, INPUT);
  pinMode(input6, INPUT);
  pinMode(input7, INPUT);
  
  pinMode(output0, OUTPUT);
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output6, OUTPUT);
  pinMode(output7, OUTPUT);
  
  Serial.begin(9600);  //Arduino Serial Monitor
}

void loop() 
{
  int comando = 0;
  int pin = 0;
  int valor = 0;
  
  if(Serial.available())
  {
    comando = Serial.read();
    switch(comando)
    {
      case 'E':
      case 'A':
      case 'L':
      case 'D':
        while(!Serial.available()){}
        pin = Serial.read();
        //Serial.write(comando);
        //Serial.write(pin);
        break;
      default:
        comando = 0;
        break;
    }
  }
  
  switch(comando)
  {
    case 69://E
      switch(pin)
      {
        case 48://0
          digitalWrite(output0, HIGH);
          break;
        case 49://1
          digitalWrite(output1, HIGH);
          break;
        case 50://2
          digitalWrite(output2, HIGH);
          break;
        case 51://3
          digitalWrite(output3, HIGH);
          break;
        case 52://4
          digitalWrite(output4, HIGH);
          break;
        case 53://5
          digitalWrite(output5, HIGH);
          break;
        case 54://6
          digitalWrite(output6, HIGH);
          break;
        case 55://7
          digitalWrite(output7, HIGH);
          break;
        case 84://T
          digitalWrite(output0, HIGH);
          digitalWrite(output1, HIGH);
          digitalWrite(output2, HIGH);
          digitalWrite(output3, HIGH);
          digitalWrite(output4, HIGH);
          digitalWrite(output5, HIGH);
          digitalWrite(output6, HIGH);
          digitalWrite(output7, HIGH);
          break;
      }
      break;
    case 65://A
      switch(pin)
      {
        case 48://0
          digitalWrite(output0, LOW);
          break;
        case 49://1
          digitalWrite(output1, LOW);
          break;
        case 50://2
          digitalWrite(output2, LOW);
          break;
        case 51://3
          digitalWrite(output3, LOW);
          break;
        case 52://4
          digitalWrite(output4, LOW);
          break;
        case 53://5
          digitalWrite(output5, LOW);
          break;
        case 54://6
          digitalWrite(output6, LOW);
          break;
        case 55://7
          digitalWrite(output7, LOW);
          break;
        case 84://T
          digitalWrite(output0, LOW);
          digitalWrite(output1, LOW);
          digitalWrite(output2, LOW);
          digitalWrite(output3, LOW);
          digitalWrite(output4, LOW);
          digitalWrite(output5, LOW);
          digitalWrite(output6, LOW);
          digitalWrite(output7, LOW);
          break;
      }
      break;
    case 76://L
      switch(pin)
      {
        case 48://0
          valor = digitalRead(input0);
          break;
        case 49://1
          valor = digitalRead(input1);
          break;
        case 50://2
          valor = digitalRead(input2);
          break;
        case 51://3
          valor = digitalRead(input3);
          break;
        case 52://4
          valor = digitalRead(input4);
          break;
        case 53://5
          valor = digitalRead(input5);
          break;
        case 54://6
          valor = digitalRead(input6);
          break;
        case 55://7
          valor = digitalRead(input7);
          break;
        case 84://T
          valor = 0;
          if(digitalRead(input0))  valor = valor + 1;
          if(digitalRead(input1))  valor = valor + 2;
          if(digitalRead(input2))  valor = valor + 4;
          if(digitalRead(input3))  valor = valor + 8;
          if(digitalRead(input4))  valor = valor + 16;
          if(digitalRead(input5))  valor = valor + 32;
          if(digitalRead(input6))  valor = valor + 64;
          if(digitalRead(input7))  valor = valor + 128;
          break;
      }
      Serial.print(valor);
      break;
    case 68://D
      int bin;
      int i = 0;
      
      while(pin != 0)
      {
        bin = pin%2;
        pin = pin/2;
        
        switch(i)
        {
          case 0:
            if(bin != 0)  digitalWrite(output0, HIGH);
            else          digitalWrite(output0, LOW);
            break;
          case 1:
            if(bin != 0)  digitalWrite(output1, HIGH);
            else          digitalWrite(output1, LOW);
            break;
          case 2:
            if(bin != 0)  digitalWrite(output2, HIGH);
            else          digitalWrite(output2, LOW);
            break;
          case 3:
            if(bin != 0)  digitalWrite(output3, HIGH);
            else          digitalWrite(output3, LOW);
            break;
          case 4:
            if(bin != 0)  digitalWrite(output4, HIGH);
            else          digitalWrite(output4, LOW);
            break;
          case 5:
            if(bin != 0)  digitalWrite(output5, HIGH);
            else          digitalWrite(output5, LOW);
            break;
          case 6:
            if(bin != 0)  digitalWrite(output6, HIGH);
            else          digitalWrite(output6, LOW);
            break;
          case 7:
            if(bin != 0)  digitalWrite(output7, HIGH);
            else          digitalWrite(output7, LOW);
            break;
        }
        i++;
      }
      break;
  }
}
