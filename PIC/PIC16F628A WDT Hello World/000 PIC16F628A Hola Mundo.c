//	Gerardo Abraham Aguilar López

#include <16F628A.h>

#FUSES WDT                      //Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#use delay(int=4000000)

void ports_init()
{
   set_tris_a(0xFF);
   set_tris_b(0x00);
   
   output_a(0x00);
   output_b(0x00);
}

//Defines
#define LED PIN_B0
#define BTN PIN_A0

//Variables
char i;

void main()
{

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_wdt(WDT_18MS);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   ports_init();
   
    //Example blinking LED program
    while(true)
    {
      if(input(BTN))
      {
         restart_wdt();          // 0.04 mA doesn't work in proteus
         output_low(LED);
         
         for(i=1;i<=55;i++)
            sleep();
            
         output_high(LED);
         
         for(i=1;i<=56;i++)
            sleep();
      }
      else
      {
         output_low(LED);        // 1.04 mA
         delay_ms(500);
         output_high(LED);
         delay_ms(500);
      }
    }
}
