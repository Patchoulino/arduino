const int adc[] = {16};
const int POWER = 14;
const int GROUND = 17;

void setup() {
    // put your setup code here, to run once:
    int i;
    pinMode(USERLED, OUTPUT);
    pinMode(POWER, OUTPUT);
    digitalWrite(POWER, HIGH);
    pinMode(GROUND, OUTPUT);
    digitalWrite(GROUND, LOW);
    
    for (i = 0; i <= 3; i++) {
        digitalWrite(USERLED, LOW);
        delay(100);
        digitalWrite(USERLED, HIGH);
        delay(100);
    }
    
}

void loop() {
    // put your main code here, to run repeatedly:
    int value;
    int byteval;
    float floatval;
    
    value = analogRead(adc[0]);
    floatval = (value / 1023.0) * 5.0;
    byteval = value / 4;
    
    //CDC.write(byteval);
    CDC.printf("ADC: \t%u \t%u \t%.3f V \n\r",value, byteval,floatval);
    
    delay(100);
}
