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

#define CLK PIN_A0
#define LD PIN_A1
#define DAT PIN_A2

int shiftIn(void);

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
      x = shiftIn();
      printf("x = %u\t %2X ",x,x);
      int i;
      for(i = 0; i <= 7; i++)
      {
         if(bit_test(x, 7 - i))   printf("1");
         else                     printf("0");
      }
      printf("\r\n");
      delay_ms(100);
    }
}

int shiftIn(void)
{
   int byte1 = 0;
   output_bit(LD, 0);
   output_bit(LD, 1);
   int i;
   for(i = 0; i <= 7; i++)
   {
      output_bit(CLK, 0);
      if(input(DAT))      bit_set(byte1, 7 - i);
      else                bit_clear(byte1, 7 - i);
      output_bit(CLK, 1);
   }
   return byte1;
}
