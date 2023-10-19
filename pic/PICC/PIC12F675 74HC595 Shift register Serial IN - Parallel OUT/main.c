#include <12F675.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES NOCPD                    //No EE protection
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset

#use delay(int=4000000)

#define CLK PIN_A0
#define DAT PIN_A1
#define TGL PIN_A2

void shiftOut(int byte0);

void main()
{
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_comparator(NC_NC);

   int x = 0;

    while(true)
    {
      shiftOut(x);
      delay_ms(500);
      x++;
    }
}

void shiftOut(int byte0)
{
   output_bit(CLK, 0);
   output_bit(TGL, 0);
   int i;
   for(i = 0; i <= 7; i++)
   {
      if(bit_test(byte0, 7 - i))      output_bit(DAT, 1);
      else                            output_bit(DAT, 0);
      output_bit(CLK, 1);
      output_bit(CLK, 0);
   }
   output_bit(TGL, 1);
}
