#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                //Internal RC Osc, no CLKOUT
#FUSES NOPUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT                 //Reset when brownout detected
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#byte pcon    = 0x8E 
#use delay(int=4M)
//#use delay(crystal=20M)
//#use delay(clock=48M)

#use rs232(baud=9600,parity=N,xmit=PIN_B1,rcv=PIN_B0,bits=8)

#define LED PIN_B3

void main()
{
   bit_set(pcon,3);   //INTOSC = 4Mhz
   
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   set_tris_a(0);
   output_a(0);
   set_tris_b(0);
   output_b(0);
   
   int integer = 0;
   char character = "0";
   float variable = 0.1;
   
   printf("\f");
   
   while(TRUE)
   {
      printf("int = %u || c = %c || x = %.1f",integer,character,variable);
      putc(10);
      putc(13);
      
      integer++;
      character = character + 1;
      variable = variable + 1;
      
      if(integer == 255)   break;
   }
}
