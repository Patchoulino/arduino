/*
 * Servo control from 9 to 180°
 * from 0 to 8 servo gets stuck
 * and starts buzzing
 */

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 90;    // variable to store the servo position 
 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object 
  myservo.write(pos);
} 
 
void loop() 
{ 
  if(Serial.available())
  {
    int byte1 = Serial.read();
    switch(byte1)
    {
      case 'W':
        pos = pos + 10;
        break;
      case 'S':
        pos = pos - 10;
        break;
      case 'w':
        pos = pos + 1;
        break;
      case 's':
        pos = pos - 1;
        break;
      default:
        pos = byte1;
        break;
    }
    if(pos > 180) pos = 180;
    if(pos <= 0)  pos = 0;

    //int realpos = map(pos, 0, 180, 9, 180);
    int realpos = pos * 0.95 + 9;
    myservo.write(realpos);
    Serial.print("Servo pos: ");
    Serial.print(pos);
    Serial.print(" || ");
    Serial.println(realpos);
  }
} 
