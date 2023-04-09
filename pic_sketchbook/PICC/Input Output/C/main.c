#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#use delay(int=4000000)

void main()
{

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   set_tris_a(0xFF);
   set_tris_b(0x00);
   output_b(0);
   
   int x;
   
   START:
      output_b(255);
      delay_ms(200);
      output_b(0);
      delay_ms(200);
      x = x + 1;
   if(x < 3)   GOTO START;   

    while(true)
    {
      x = 0;
      
      if(input(PIN_A0)) x = x + 1;
      if(input(PIN_A1)) x = x + 2;
      if(input(PIN_A2)) x = x + 4;
      if(input(PIN_A3)) x = x + 8;
      if(input(PIN_A4)) x = x + 16;
      if(input(PIN_A5)) x = x + 32;
      if(input(PIN_A6)) x = x + 64;
      if(input(PIN_A7)) x = x + 128;
      
      output_b(x);
      
      delay_ms(50);
    }

}
