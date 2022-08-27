void setup() {
    // put your setup code here, to run once:
    int i;
    pinMode(USERLED, OUTPUT);
    
    for (i = 0; i <= 3; i++) {
        digitalWrite(USERLED, LOW);
        delay(500);
        digitalWrite(USERLED, HIGH);
        delay(500);
    }
    
}

void loop() {
    // put your main code here, to run repeatedly:
    int c = 32;
    int byte0;
    
    while(c != '@'){
    c = CDC.getKey();
    CDC.printf("%c",c);
    if(c == '.')    CDC.printf("\r\n");
    if(c == 'e' || c == 'E')    digitalWrite(USERLED, HIGH);
    if(c == 'a' || c == 'A')    digitalWrite(USERLED, LOW);
    if(c == 't' || c == 'T')    toggle(USERLED);
    }
    
    CDC.printf("\r\nASCII TABLE!\r\n");
    for(byte0 = 32; byte0 <= 126; byte0++)
    {
        CDC.printf("Char: %c || Dec: %u\r\n",byte0,byte0);
    }
}
