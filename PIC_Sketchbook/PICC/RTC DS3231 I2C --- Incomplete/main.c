#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#byte pcon    = 0x8E 
#use delay(int=4M)

#use rs232(baud=9600,parity=N,xmit=PIN_B3,rcv=PIN_B2,bits=8)

#include <DS3231.C>
#use i2c(Master, SDA=pin_B4, SCL=pin_B5)

unsigned char s = 10;                    
unsigned char min = 10;              
unsigned char hr = 10;    
unsigned char dy = 1;    
unsigned char dt = 31;              
unsigned char mt = 12;                    
unsigned char yr = 99; 
short hr_format = _12_hour_format; 
short am_pm = 1; 
   
void main()
{
   bit_set(pcon,3);   //INTOSC = 4Mhz

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   DS3231_init();

    //Example blinking LED program
    while(true){
      output_low(LED);
      delay_ms(1000);
      output_high(LED);
      delay_ms(1000);
    }

}
