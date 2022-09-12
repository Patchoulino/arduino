#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES NOPUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT                 //Reset when brownout detected
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#byte pcon    = 0x8e 

#use delay(int=48k)

//*********************** Declaracion de pines ****************
#define LED PIN_A0

void startup(void)
{
   set_tris_a(0);    output_a(0);
   set_tris_b(0);    output_b(0);
}

void main()
{

   bit_clear(pcon,3);   // INTOSC = 48Khz
   //bit_set(pcon,3);   //INTOSC = 4Mhz

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   startup();
   
    while(true)
    {
      
      output_toggle(LED);
      delay_ms(100);
      output_toggle(LED);
      delay_ms(900);
      
    }

}

