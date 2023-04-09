#include <12F683.h>
#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES NOCPD                    //No EE protection
#FUSES NOPROTECT                //Code not protected from reading
#FUSES MCLR                     //Master Clear pin enabled
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOIESO                   //Internal External Switch Over mode disabled
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled

#use delay(int=8000000)

#define BTN PIN_A5

void main()
{

   setup_oscillator(OSC_8MHZ);

   setup_adc_ports(sAN3|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,255,1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(512);
   setup_comparator(NC_NC);
   
   long adc_value_1;
   long adc_value_3;

   while(true)
   {
      set_adc_channel(1);
      delay_us(10);
      adc_value_1 = read_adc();
      delay_us(10);
   
      set_adc_channel(3);
      delay_us(10);
      adc_value_3 = read_adc();
      delay_us(10);
      
      if(adc_value_1 < adc_value_3) set_pwm1_duty(1024 - adc_value_1);
      else                          set_pwm1_duty(1024 - adc_value_3);
   }
}
