const int led[] = {17, 18, 19, 20};

void setup() {
    // put your setup code here, to run once:
    int i;
    pinMode(USERLED, OUTPUT);
    
    for (i = 0; i <= 3; i++) {
        pinMode(led[i], OUTPUT);
        digitalWrite(led[i], HIGH);
        
        digitalWrite(USERLED, LOW);
        delay(500);
        digitalWrite(USERLED, HIGH);
        delay(500);
    }
    
}

void loop() {
    // put your main code here, to run repeatedly:
    int i;
    for (i = 0; i <= 3; i++){
        toggle(led[i]);
    }
    toggle(USERLED);
    delay(100);
}
