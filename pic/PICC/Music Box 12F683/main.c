#include <12F683.h>
#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES NOCPD                    //No EE protection
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOIESO                   //Internal External Switch Over mode disabled
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled

#use delay(int=8000000)

#define TONE_PIN  PIN_A0
#include <TONES.C>

#define btn PIN_A3

void main()
{

   setup_oscillator(OSC_8MHZ);

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,255,1);  //500Hz
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC);
  
    while(true)
    {
      if(input(btn))
      {
         while(input(btn)){}
         
         generate_tone(660,100);
         delay_ms(150);
         generate_tone(660,100);
         delay_ms(300);
         generate_tone(510,100);
         delay_ms(300);
         generate_tone(660,100);
         delay_ms(100);
         generate_tone(770,100);
         delay_ms(300);
         generate_tone(380,100);
         delay_ms(550);
         generate_tone(510,100);
         delay_ms(575);
         generate_tone(380,100);
         delay_ms(450);
         generate_tone(320,100);
         delay_ms(400);
         generate_tone(440,100);
         delay_ms(500);
         generate_tone(480,100);
         delay_ms(300);
         generate_tone(450,100);
         delay_ms(330);
         
         generate_tone(430,100);
         delay_ms(300);
         generate_tone(380,100);
         delay_ms(200);
         generate_tone(660,100);
         delay_ms(200);
         generate_tone(760,100);
         delay_ms(150);
         generate_tone(860,100);
         delay_ms(300);
         generate_tone(700,100);
         delay_ms(150);
         generate_tone(760,100);
         delay_ms(350);
         generate_tone(660,100);
         delay_ms(300);
         generate_tone(520,100);
         delay_ms(150);
         generate_tone(580,100);
         delay_ms(150);
         generate_tone(480,100);
         delay_ms(500);
         generate_tone(510,100);
         delay_ms(450);
         generate_tone(380,100);
         delay_ms(400);
         generate_tone(320,100);
         delay_ms(500);
         generate_tone(440,100);
         delay_ms(300);
         generate_tone(480,100);
         delay_ms(330);
         generate_tone(450,100);
         delay_ms(150);
         generate_tone(430,100);
         delay_ms(300);
         generate_tone(380,100);
         delay_ms(200);
      }
    }
}
