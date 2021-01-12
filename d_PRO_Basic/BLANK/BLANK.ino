/*
WDP3 WDP2 WDP1 WDP0
        Number of WDT Oscillator  Cycles  
                          Typical Time-out at VCC = 5.0V
0 0 0 0 2K (2048) cycles        16ms
0 0 0 1 4K (4096) cycles        32ms
0 0 1 0 8K (8192) cycles        64ms
0 0 1 1 16K (16384) cycles      0.125 s
0 1 0 0 32K (32768) cycles      0.25 s
0 1 0 1 64K (65536) cycles      0.5 s
0 1 1 0 128K (131072) cycles    1.0 s
0 1 1 1 256K (262144) cycles    2.0 s
1 0 0 0 512K (524288) cycles    4.0 s
1 0 0 1 1024K (1048576) cycles  8.0 s
 */
#define LED_PIN LED_BUILTIN

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  //Save Power by writing all Digital IO LOW - note that pins just need to be tied one way or another, do not damage devices!
  for (int i = 0; i < 20; i++) {
    //if(i != 2)//just because the button is hooked up to digital pin 2
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  
  //attachInterrupt(0, digitalInterrupt, FALLING); //interrupt for waking up
  
  //SETUP WATCHDOG TIMER
  WDTCSR = 24;//change enable and WDE - also resets
  WDTCSR = 33;//prescalers only - get rid of the WDE and WDCE bit
  WDTCSR |= (1 << 6);//enable interrupt mode
  WDTCSR = WDTCSR & B11011000 | B00000110; //  
  
  //Disable ADC - don't forget to flip back after waking up if using ADC in your application ADCSRA |= (1 << 7);
  ADCSRA &= ~(1 << 7);
  
  //ENABLE SLEEP - this enables the sleep mode
  SMCR |= (1 << 2); //power down mode
  SMCR |= 1;//enable sleep
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  goodnight();
  digitalWrite(LED_PIN, LOW);
  goodnight();  
}

void goodnight(){
  //BOD DISABLE - this must be called right before the __asm__ sleep instruction
  MCUCR |= (3 << 5); //set both BODS and BODSE at the same time
  MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); //then set the BODS bit and clear the BODSE bit at the same time
  __asm__  __volatile__("sleep");//in line assembler to go to sleep
}

ISR(WDT_vect){  // watchdog interrupt
  //DON'T FORGET THIS!  Needed for the watch dog timer.  This is called after a watch dog timer timeout - this is the interrupt function called after waking up
}

//void digitalInterrupt(){
  //needed for the digital input interrupt
//}
