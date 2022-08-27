#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#use delay(int=4000000)

#include <LCD.C>
#include <KBD.C>

void ports_init()
{
   set_tris_a(0x00);
   set_tris_b(0x00);
   
   output_a(0x00);
   output_b(0x00);
}

//Defines


//Variables
char i;

void main()
{

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   rtc_init();
   lcd_init();
   kbd_init();

   char k;

   lcd_init();
   kbd_init();

   lcd_putc("\fReady...\n");

   while (TRUE) 
   {
      k=kbd_getc();
      if(k!=0)
        if(k=='*')
          lcd_putc('\f');
        else
          lcd_putc(k);
   }
}

