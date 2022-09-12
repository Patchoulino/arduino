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
const int adc0 = 13;

int position = 90;

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
    delay(3000);
}  

void loop(void)
{
    position = analogRead(adc0) / 4;
    CDC.printf("Servo position = %u\r\n",position);
    servo.write(MYSERVO, position);
    toggle(USERLED);
    delay(100);
}
