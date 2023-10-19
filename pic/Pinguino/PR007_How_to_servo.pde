// Servo library test with Pinguino
// Connect servo control lines to pinguino pins.
// Feed servos with +5 V:
//
//   +-----+
//   |servo|--------- PWM Servo control ---> to pinguino pin.
//   |     |--------- +5V
//   |  o  |--------- GND
//   |     | 
//   +-----+

//#define MYSERVO 0   // servo attached to pin 0

const int MYSERVO = 0;

int position = 90;
int dir = 1;

void setup(void)
{
    int i;
    CDC.printf("DERP");
    pinMode(USERLED, OUTPUT);
    
    for (i = 0; i <= 3; i++) {
        digitalWrite(USERLED, LOW);
        delay(100);
        digitalWrite(USERLED, HIGH);
        delay(100);
    } 
    servo.attach(MYSERVO);
    servo.setMinimumPulse(MYSERVO, 560);
    servo.setMaximumPulse(MYSERVO, 2000);
    servo.write(MYSERVO, 90);
    delay(3000);
}  

void loop(void)
{
    servo.write(MYSERVO, position);
    position = position + dir;
    if (position>=180) dir = -1;
    if (position<1)   dir = 1;
    toggle(USERLED);
    delay(10);
}