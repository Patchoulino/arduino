const int adc[] = {17, 18, 19, 20};
const int pwm[] = {11, 12};

void setup() {
    // put your setup code here, to run once:
    int i;
    pinMode(USERLED, OUTPUT);
    
    for (i = 0; i <= 3; i++) {
        digitalWrite(USERLED, LOW);
        delay(100);
        digitalWrite(USERLED, HIGH);
        delay(100);
    }
    
}

void loop() {
    // put your main code here, to run repeatedly:
    int i;
    int value;
    for (i = 0; i <= 3; i++){
        value = analogRead(adc[i]);
        CDC.printf("| A%u: %u |",i,value);
    }
    
    analogWrite(pwm[0], value/4);
    analogWrite(pwm[1], (1023 - value)/4);
    
    delay(100);
    CDC.printf("\r\n");
}
