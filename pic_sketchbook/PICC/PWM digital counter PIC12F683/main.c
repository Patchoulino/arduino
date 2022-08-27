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

#define led_red PIN_A0
#define led_grn PIN_A1
#define led_blu PIN_A2

#define btn_red PIN_A5
#define btn_grn PIN_A4
#define btn_blu PIN_A3

void rgb(int red, int grn, int blu, int time);

void main()
{

   setup_oscillator(OSC_8MHZ);

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,255,1);  //500Hz
   setup_ccp1(CCP_OFF);
   //setup_ccp1(CCP_PWM);
   //set_pwm1_duty(0);
   setup_comparator(NC_NC);
   
   set_tris_a(0b111000);
   
   int count_red = 0;
   int count_grn = 0;
   int count_blu = 0;
   
    while(true)
    {
      if(input(btn_red))   count_red = count_red + 25;
      if(input(btn_grn))   count_grn = count_grn + 25;
      if(input(btn_blu))   count_blu = count_blu + 25;
      
      if(count_red > 100)  count_red = 0;
      if(count_grn > 100)  count_grn = 0;
      if(count_blu > 100)  count_blu = 0;
          
      rgb(count_red, count_grn, count_blu, 100);
    }
}

void rgb(int red, int grn, int blu, int time)
{  
   int i;                              //time 1 = 1ms
   for(i = 0; i < time; i++)
   {
      if(red > 0) output_bit(led_red,1);
      if(grn > 0) output_bit(led_grn,1);
      if(blu > 0) output_bit(led_blu,1);
      
      int j;
      for(j = 1; j <= 100; j++)
      {
         if(j > red) output_bit(led_red,0);
         if(j > grn) output_bit(led_grn,0);
         if(j > blu) output_bit(led_blu,0);
         delay_us(10);
      }
   }
}
