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
    
    Serial.begin(9600);
}

char byte_rs232;
char byte_cdc;

void loop() {
    // put your main code here, to run repeatedly:
    if(Serial.available())
    {
        byte_rs232 = Serial.read();
        CDC.write(byte_rs232);
        Serial.write(byte_rs232);
    }
}
