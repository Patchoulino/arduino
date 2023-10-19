const int led[] = {20, 19, 18, 17};
const int btn[] = {0, 1, 2, 3};

void setup() {
    // put your setup code here, to run once:
    int i;
    pinMode(USERLED, OUTPUT);
    
    for (i = 0; i <= 3; i++) {
        pinMode(led[i], OUTPUT);
        pinMode(btn[i], INPUT);
        
        digitalWrite(USERLED, LOW);
        delay(100);
        digitalWrite(USERLED, HIGH);
        delay(100);
    }
    
}

void loop() {
    // put your main code here, to run repeatedly:
    int i;
    for (i = 0; i <= 3; i++){
        if (digitalRead(btn[i]) == HIGH)    digitalWrite(led[i], HIGH);
        else                                             digitalWrite(led[i], LOW);
    }
    delay(100);
}
