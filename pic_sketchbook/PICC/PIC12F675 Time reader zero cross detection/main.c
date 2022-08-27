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
#use rs232(baud=9600,parity=N,xmit=PIN_A5,rcv=PIN_A4,bits=8)

#define IN  PIN_A0

void main()
{
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_comparator(NC_NC);

   long long i;

    while(true)
    {
      i = 0;
      while(!input(IN)){}
      while(input(IN)){}
      while(!input(IN))
      {
         i++;
         delay_us(1);
      }
      printf("time = %Lu",i);
      printf("\r\n");
      delay_ms(100);
    }
}
