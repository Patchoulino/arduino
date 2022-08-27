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

#define btn_1 PIN_A1
#define btn_2 PIN_A2
#define btn_3 PIN_A3
#define btn_4 PIN_A4
#define btn_5 PIN_A5

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
      if(input(btn_1)) generate_tone(C_NOTE[1], 100);
      if(input(btn_2)) generate_tone(D_NOTE[1], 100);
      if(input(btn_3)) generate_tone(E_NOTE[1], 100);
      if(input(btn_4)) generate_tone(Gb_NOTE[1], 100);
      if(input(btn_5)) generate_tone(Ab_NOTE[1], 100);
      delay_us(1);
    }
}
