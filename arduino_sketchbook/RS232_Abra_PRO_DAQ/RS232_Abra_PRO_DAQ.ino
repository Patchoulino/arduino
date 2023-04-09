/*
 * -----------------------------------------------------------
 * PRO_DAQ written by Patchoulino 25/10/2015
 * -----------------------------------------------------------
 * -------------------List of commands------------------------
 * -----------------------------------------------------------
 * -----C   Configures the digital pins for input or ourput---
 *     "C50" = Configure dig5(pin13) as OUTPUT
 *     "C01" = Configure dig0(pin2) as INPUT
 * -----------------------------------------------------------
 * -----R   Configures and reads a digital pin, returns 0-1---
 *     "R1" = Configure dig5(pin4) as INPUT and returns 0-1
 *     "R4" = Configure dig0(pin12) as INPUT and returns 0-1
 *     When using this commando with W, make sure to
 *     write OUTPUT LOW before start reading the pin again
 *     as it will forever be latched to HIGH
 * -----------------------------------------------------------
 * -----W   Configures and writes a digital pin HIGH or LOW---
 *     "W21" = Configure dig5(pin7) as OUTPUT HIGH
 *     "W30" = Configure dig0(pin8) as OUTPUT LOW
 * -----------------------------------------------------------
 * -----A   Reads an analog pin and returns 0-255-------------
 *     "A0" = Reads "A0" and sends it's value 0-255
 *     "A5" = Reads "A5" and sends it's value 0-255
 * -----------------------------------------------------------
 * -----P   Writes PWM to the pwm specific pins from 0-255----
 *     "P1!" = Writes to PWM1(pin5) the decimal value of "!"
 *             '!' = 33 (12.94% Duty)
 *     "P4~" = Writes to PWM4(pin10) the decimal value of "~"
 *             '~' = 126 (49.41% Duty)
 * -----------------------------------------------------------
 * -----S   Attaches a Servo motor into the specific digital--
 *          pin, when this occurs, the pin can no longer be---
 *          used as input or output---------------------------
 *          the readed value is mapped from 0-180 to 9-180----
 *          as the values between 1-8 make hobby servos noisy-
 *     "S0!" = Writes to Servo0(pin2) the decimal value of "!"
 *             '!' = 33°
 *     "S5~" = Writes to Servo5(pin13) the decimal value of "~"
 *             '~' = 126°
 * -----------------------------------------------------------
 */
// Change to 1 when using Arduino Serial Monitor for testing
const short Arduino_Serial_Monitor = 1;

const int dig0 = 2;   const int pwm0 = 3;
const int dig1 = 4;   const int pwm1 = 5;
const int dig2 = 7;   const int pwm2 = 6;
const int dig3 = 8;   const int pwm3 = 9;
const int dig4 = 12;  const int pwm4 = 10;
const int dig5 = 13;  const int pwm5 = 11;

#include <Servo.h>

Servo srv0;   int srv0_pos = 90;
Servo srv1;   int srv1_pos = 90;
Servo srv2;   int srv2_pos = 90;
Servo srv3;   int srv3_pos = 90;
Servo srv4;   int srv4_pos = 90;
Servo srv5;   int srv5_pos = 90;

void setup() 
{
  Serial.begin(9600);  //Arduino Serial Monitor
}

void loop() 
{
  int command = 0;
  int pin = 0;
  int Byte0 = 0;
  
  if(Serial.available())
  {
    command = Serial.read();
    switch(command)
    {
      case 'C': //Configure digital pins as INPUTS or OUTPUTS
      case 'R': //Reads digital pins and sends 0 or 1
      case 'W': //Writes digital pins as LOW or HIGH
      case 'A': //Reads analog pins and sends 0 to 255
      case 'P': //Writes PWM to analog outputs from 0 to 255
      case 'S': //Control Servo motor position from 0 to 180°
        while(!Serial.available()){}
        pin = Serial.read();
        if(command == 'C' || command == 'W' || command == 'P' || command == 'S')
        {
          while(!Serial.available()){}
          Byte0 = Serial.read();
        }
        break;
      case '.':
        Serial.write(10);
        Serial.write(13);
        break;
      default: //Used to confirm DAQ Communication
        Serial.write(command);
        break;
    }
  }
  
  switch(command)
  {
    case 'C':
      switch(pin)
      {
        case '0':
          if(Byte0 == '1')
          {
            pinMode(dig0, INPUT);
          }
          else
          {
            pinMode(dig0, OUTPUT);
          }
          break;
        case '1':
          if(Byte0 == '1')
          {
            pinMode(dig1, INPUT);
          }
          else
          {
            pinMode(dig1, OUTPUT);
          }
          break;
        case '2':
          if(Byte0 == '1')
          {
            pinMode(dig2, INPUT);
          }
          else
          {
            pinMode(dig2, OUTPUT);
          }
          break;
        case '3':
          if(Byte0 == '1')
          {
            pinMode(dig3, INPUT);
          }
          else
          {
            pinMode(dig3, OUTPUT);
          }
          break;
        case '4':
          if(Byte0 == '1')
          {
            pinMode(dig4, INPUT);
          }
          else
          {
            pinMode(dig4, OUTPUT);
          }
          break;
        case '5':
          if(Byte0 == '1')
          {
            pinMode(dig5, INPUT);
          }
          else
          {
            pinMode(dig5, OUTPUT);
          }
          break;
      }
      break;
    case 'R':
      switch(pin)
      {
        case '0':
          digitalWrite(dig0, LOW);
          pinMode(dig0, INPUT);
          Byte0 = digitalRead(dig0);
          if(Arduino_Serial_Monitor) Serial.print("pin_2 : ");
          break;
        case '1':
          digitalWrite(dig1, LOW);
          pinMode(dig1, INPUT);
          Byte0 = digitalRead(dig1);
          if(Arduino_Serial_Monitor) Serial.print("pin_4 : ");
          break;
        case '2':
          digitalWrite(dig2, LOW);
          pinMode(dig2, INPUT);
          Byte0 = digitalRead(dig2);
          if(Arduino_Serial_Monitor) Serial.print("pin_7 : ");
          break;
        case '3':
          digitalWrite(dig3, LOW);
          pinMode(dig3, INPUT);
          Byte0 = digitalRead(dig3);
          if(Arduino_Serial_Monitor) Serial.print("pin_8 : ");
          break;
        case '4':
          digitalWrite(dig4, LOW);
          pinMode(dig4, INPUT);
          Byte0 = digitalRead(dig4);
          if(Arduino_Serial_Monitor) Serial.print("pin_12 : ");
          break;
        case '5':
          digitalWrite(dig5, LOW);
          pinMode(dig5, INPUT);
          Byte0 = digitalRead(dig5);
          if(Arduino_Serial_Monitor) Serial.print("pin_13 : ");
          break;
        case 'T':
          digitalWrite(dig0, LOW);
          digitalWrite(dig1, LOW);
          digitalWrite(dig2, LOW);
          digitalWrite(dig3, LOW);
          digitalWrite(dig4, LOW);
          digitalWrite(dig5, LOW);
          pinMode(dig0, INPUT);
          pinMode(dig1, INPUT);
          pinMode(dig2, INPUT);
          pinMode(dig3, INPUT);
          pinMode(dig4, INPUT);
          pinMode(dig5, INPUT);
          if(digitalRead(dig0)) Byte0 = Byte0 + 1;
          if(digitalRead(dig1)) Byte0 = Byte0 + 2;
          if(digitalRead(dig2)) Byte0 = Byte0 + 4;
          if(digitalRead(dig3)) Byte0 = Byte0 + 8;
          if(digitalRead(dig4)) Byte0 = Byte0 + 16;
          if(digitalRead(dig5)) Byte0 = Byte0 + 32;
          if(Arduino_Serial_Monitor) Serial.print("all_pins : ");
          break;
      }
      if(Arduino_Serial_Monitor)
      {
        Serial.println(Byte0);
      }
      else
      {
        Serial.write(Byte0);
      }
      break;
    case 'W':
      switch(pin)
      {
        case '0':
          pinMode(dig0, OUTPUT);
          if(Byte0 == '1')
          {
            digitalWrite(dig0, HIGH);
          }
          else
          {
            digitalWrite(dig0, LOW);
          }
          break;
        case '1':
          pinMode(dig1, OUTPUT);
          if(Byte0 == '1')
          {
            digitalWrite(dig1, HIGH);
          }
          else
          {
            digitalWrite(dig1, LOW);
          }
          break;
        case '2':
          pinMode(dig2, OUTPUT);
          if(Byte0 == '1')
          {
            digitalWrite(dig2, HIGH);
          }
          else
          {
            digitalWrite(dig2, LOW);
          }
          break;
        case '3':
          pinMode(dig3, OUTPUT);
          if(Byte0 == '1')
          {
            digitalWrite(dig3, HIGH);
          }
          else
          {
            digitalWrite(dig3, LOW);
          }
          break;
        case '4':
          pinMode(dig4, OUTPUT);
          if(Byte0 == '1')
          {
            digitalWrite(dig4, HIGH);
          }
          else
          {
            digitalWrite(dig4, LOW);
          }
          break;
        case '5':
          pinMode(dig5, OUTPUT);
          if(Byte0 == '1')
          {
            digitalWrite(dig5, HIGH);
          }
          else
          {
            digitalWrite(dig5, LOW);
          }
          break;
        case 'T':
          pinMode(dig0, OUTPUT);
          pinMode(dig1, OUTPUT);
          pinMode(dig2, OUTPUT);
          pinMode(dig3, OUTPUT);
          pinMode(dig4, OUTPUT);
          pinMode(dig5, OUTPUT);
          int bin = 0;
          int i;
          while(Byte0 != 0)
          {
            bin = Byte0%2;
            Byte0 = Byte0/2;
            
            switch(i)
            {
              case 0:
                if(bin != 0)  digitalWrite(dig0, HIGH);
                else          digitalWrite(dig0, LOW);
                break;
              case 1:
                if(bin != 0)  digitalWrite(dig1, HIGH);
                else          digitalWrite(dig1, LOW);
                break;
              case 2:
                if(bin != 0)  digitalWrite(dig2, HIGH);
                else          digitalWrite(dig2, LOW);
                break;
              case 3:
                if(bin != 0)  digitalWrite(dig3, HIGH);
                else          digitalWrite(dig3, LOW);
                break;
              case 4:
                if(bin != 0)  digitalWrite(dig4, HIGH);
                else          digitalWrite(dig4, LOW);
                break;
              case 5:
                if(bin != 0)  digitalWrite(dig5, HIGH);
                else          digitalWrite(dig5, LOW);
                break;
            }
            i++;
          }
          break;
      }
      break;
    case 'A':
      switch(pin)
      {
        case '0':
          Byte0 = analogRead(A0);
          if(Arduino_Serial_Monitor) Serial.print("A0 : ");
          break;
        case '1':
          Byte0 = analogRead(A1);
          if(Arduino_Serial_Monitor) Serial.print("A1 : ");
          break;
        case '2':
          Byte0 = analogRead(A2);
          if(Arduino_Serial_Monitor) Serial.print("A2 : ");
          break;
        case '3':
          Byte0 = analogRead(A3);
          if(Arduino_Serial_Monitor) Serial.print("A3 : ");
          break;
        case '4':
          Byte0 = analogRead(A4);
          if(Arduino_Serial_Monitor) Serial.print("A4 : ");
          break;
        case '5':
          Byte0 = analogRead(A5);
          if(Arduino_Serial_Monitor) Serial.print("A5 : ");
          break;
      }
      Byte0 = Byte0 / 4;
      if(Arduino_Serial_Monitor)
      {
        Serial.println(Byte0);
      }
      else
      {
        Serial.write(Byte0);
      }
      break;
    case 'P':
      switch(pin)
      {
        case '0':
          analogWrite(pwm0, Byte0);
          break;
        case '1':
          analogWrite(pwm1, Byte0);
          break;
        case '2':
          analogWrite(pwm2, Byte0);
          break;
        case '3':
          analogWrite(pwm3, Byte0);
          break;
        case '4':
          analogWrite(pwm4, Byte0);
          break;
        case '5':
          analogWrite(pwm5, Byte0);
          break;
      }
      break;
    case 'S':
      if(Byte0 > 180) Byte0 = 180;
      switch(pin)
      {
        case '0':
          srv0.attach(dig0);
          srv0_pos = Byte0 * 0.95 + 9;  //map(Byte0, 0, 180, 9, 180);
          srv0.write(srv0_pos);
          break;
        case '1':
          srv1.attach(dig1);
          srv1_pos = Byte0 * 0.95 + 9;
          srv1.write(srv1_pos);
          break;
        case '2':
          srv2.attach(dig2);
          srv2_pos = Byte0 * 0.95 + 9;
          srv2.write(srv2_pos);
          break;
        case '3':
          srv3.attach(dig3);
          srv3_pos = Byte0 * 0.95 + 9;
          srv3.write(srv3_pos);
          break;
        case '4':
          srv4.attach(dig4);
          srv4_pos = Byte0 * 0.95 + 9;
          srv4.write(srv4_pos);
          break;
        case '5':
          srv5.attach(dig5);
          srv5_pos = Byte0 * 0.95 + 9;
          srv5.write(srv5_pos);
          break;
      }
      break;
  }
}

/*
 * Sending Serial.print sends char by char the number made
 * AN0  ->  printf(171) ->  pc  ->  1 ,  7 ,  1   by its own
 * Sending Serial.write sends the char and that's it
 * AN0  ->  write(171)  ->  pc  ->  Chr(171) = ¬
 * Use print for Arduino Serial Monitor, write for byte control
 * on external program (Visual Basic, DevC, LabVIEW, Matlab, etc...)
 */
