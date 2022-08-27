/*
	Blink a LED
*/

const int pin = 29;

void setup()
{
    // initialize the digital pin USERLED as an output.
    pinMode(pin, OUTPUT);   
}

void loop()
{
    digitalWrite(pin, HIGH);
    delay(1000);		     // wait for 500ms
    digitalWrite(pin, LOW);
    delay(1000);		     // wait for 500ms
}
