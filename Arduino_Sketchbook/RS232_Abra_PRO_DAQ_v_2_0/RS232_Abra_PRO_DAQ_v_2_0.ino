/*
 * -----------------------------------------------------------
 * PRO_DAQ written by Patchoulino 10/2015
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
 *     "RT" = Configures all digital pins as INPUTs and
 *            returns a byte(0-63) value corresponding the
 *            binary value of the pins.  b010101 = 21
 *            pin5  pin4  pin3  pin2  pin1  pin0    all
 *            +32   +16   +8    +4    +2    +1   =  0~63
 * -----------------------------------------------------------
 * -----W   Configures and writes a digital pin HIGH or LOW---
 *     "W21" = Configure dig5(pin7) as OUTPUT HIGH
 *     "W30" = Configure dig0(pin8) as OUTPUT LOW
 *     "WTX" = Configures all digital pins as OUTPUTs and
 *             decodes the char sent to binary to write to
 *             each pin.  'X' = 88 = b[01]011000
 *            pin5  pin4  pin3  pin2  pin1  pin0 
 *             0     1     1     0     0     0   
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
 *          used as output------------------------------------
 *          the readed value can be mapped from to 9-180------
 *          as the values between 1-8 make hobby servos noisy-
 *     "S0 " = Writes to Servo0(pin2) the decimal value of " "
 *             ' ' = 32°
 *     "S2Z" = Writes to Servo2(pin7) the decimal value of "Z"
 *             'Z' = 90°
 *     "S5~" = Writes to Servo5(pin13) the decimal value of "~"
 *             '~' = 126°
 * -----------------------------------------------------------
 */

#include "Streaming.h"

// Change to 1 when using Arduino Serial Monitor for testing
const short Arduino_Serial_Monitor = 1;

const int dig[] = {2, 4, 7, 8, 12, 13};
const int pwm[] = {3, 5, 6, 9, 10, 11};
const int adc[] = {A0, A1, A2, A3, A4, A5};

#include <Servo.h>
Servo srv[6];

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
        if(isDigit(pin))  pin = pin - '0';  //Convert Chr to Int
        else  if(pin != 'T')  command = 0;  //To avoid random pin values
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
      if(Byte0 == '0')  pinMode(dig[pin], OUTPUT);
      else              pinMode(dig[pin], INPUT);
      if(Arduino_Serial_Monitor)  Serial << "Configured Digital Pin: " << pin << " as " << _BYTE(Byte0) << endl;
      break;
    case 'R':
      if(pin == 'T')
      {
        for(int i = 0; i <= (sizeof(dig) / 2 - 1); i++)
        {
          digitalWrite(dig[i], LOW);
          pinMode(dig[i], INPUT);
          if(digitalRead(dig[i])) Byte0 += pow(2, i);
        }
        if(Arduino_Serial_Monitor)  Serial << "Read Digital Pin: ALL = ";
      }
      else
      {
        digitalWrite(dig[pin], LOW);
        pinMode(dig[pin], INPUT);
        Byte0 = digitalRead(dig[pin]);
        if(Arduino_Serial_Monitor)  Serial << "Read Digital Pin: " << pin << " = ";
      }
      if(Arduino_Serial_Monitor)  Serial.println(Byte0);
      else                        Serial.write(Byte0);
      break;
    case 'W':
      if(pin == 'T')
      {
        if(Arduino_Serial_Monitor)  Serial << "Wrote Digital Pin: ALL as " << Byte0 << endl;
        int bin;
        for(int i = 0; i <= (sizeof(dig) / 2 - 1); i++)
        {
          pinMode(dig[i], OUTPUT);
          bin = Byte0 % 2;
          Byte0 = Byte0 / 2;
          if(bin != 0)  digitalWrite(dig[i], HIGH);
          else          digitalWrite(dig[i], LOW);
        }
      }
      else
      {
        pinMode(dig[pin], OUTPUT);
        if(Byte0 == '1')  digitalWrite(dig[pin], HIGH);
        else              digitalWrite(dig[pin], LOW);
        if(Arduino_Serial_Monitor)  Serial << "Wrote Digital Pin: " << pin << " as " << _BYTE(Byte0) << endl;
      }
      break;
    case 'A':
      Byte0 = analogRead(adc[pin]) / 4;
      if(Arduino_Serial_Monitor)  Serial << "Read Analog(ADC) pin: " << pin << " = " << Byte0 << endl; 
      else                        Serial.write(Byte0);
      break;
    case 'P':
      analogWrite(pwm[pin], Byte0);
      if(Arduino_Serial_Monitor)  Serial << "Wrote Analog(PWM) pin: " << pin << " as " << Byte0 << endl;
      break;
    case 'S':
      if(Byte0 > 180) Byte0 = 180;
      //Byte0 = Byte0 * 0.95 + 9;  //map(Byte0, 0, 180, 9, 180);
      srv[pin].attach(dig[pin]);
      srv[pin].write(Byte0);
      if(Arduino_Serial_Monitor)  Serial << "Wrote Servo pin: " << pin << " as " << Byte0 << endl;
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
