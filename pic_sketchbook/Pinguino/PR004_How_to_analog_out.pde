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
    int time = 10;
    
    for (i = 0; i <= 255; i++){
        analogWrite(pwm[0], i);
        analogWrite(pwm[1], 255 - i);
        CDC.printf("| PWM[0]: %u || PWM[1]: %u |\r\n",i,255-i);
        delay(time);
    }
    
    for (i = 255; i >= 0; i--){
        analogWrite(pwm[0], i);
        analogWrite(pwm[1], 255 - i);
        CDC.printf("| PWM[0]: %u || PWM[1]: %u |\r\n",i,255-i);
        delay(time);
    }
}
