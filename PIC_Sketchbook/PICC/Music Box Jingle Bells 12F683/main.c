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

#define BTN PIN_A3

int quartet = 0;
const int duration = 100;
const int pause = 100;
int i;

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
      quartet++;
      if(quartet == 3)  quartet = 0;
      
      delay_ms(3000);
      
      //if(input(BTN))
      if(TRUE)
      {
         //while(input(BTN)){delay_ms(1);}
         
         for(i = 0; i <= 1; i++)
         {
            generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
            generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
            generate_tone(E_NOTE[quartet], duration*2);  delay_ms(pause*2);
         }
         generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(G_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(C_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(D_NOTE[quartet], duration/2);  delay_ms(pause);
         
         generate_tone(E_NOTE[quartet], duration*2);  delay_ms(pause*2);
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(F_NOTE[quartet], duration/2);  delay_ms(pause);
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(E_NOTE[quartet], duration/2);  
         generate_tone(E_NOTE[quartet], duration/2);  delay_ms(pause);
         
         generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(D_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(D_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(D_NOTE[quartet], duration*2);  delay_ms(pause*2);
         generate_tone(G_NOTE[quartet], duration*2);  delay_ms(pause*2);
         for(i = 0; i <= 1; i++)
         {
            generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
            generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
            generate_tone(E_NOTE[quartet], duration*2);  delay_ms(pause*2);
         }
         
         generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(G_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(C_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(D_NOTE[quartet], duration/2);  delay_ms(pause);
         generate_tone(E_NOTE[quartet], duration*2);  delay_ms(pause*2);
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(E_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(E_NOTE[quartet], duration/2);  
         generate_tone(E_NOTE[quartet], duration/2);  delay_ms(pause);
         generate_tone(G_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(G_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(F_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(D_NOTE[quartet], duration);    delay_ms(pause);
         generate_tone(C_NOTE[quartet], duration*2);  delay_ms(pause*2);
      }
    }
}
