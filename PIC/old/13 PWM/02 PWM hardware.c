#include <18F4550.h>
#include <18Fmap.h>
#device adc=8

#include <18Fconfig1.h>


#use delay(clock=48000000)//Frecuencia de reloj


void main()
{

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab


   
   set_tris_a(0x0);                   //configura la puerto a como salidas
   set_tris_c(0x0);                   //configura la puerto c como salidas
   set_tris_d(0x0);                   //configura la puerto d como salidas

   
   // TODO: USER CODE!!
   int i;
   
   
   for (i=1;i<3;i++)
   {
      output_c(0);
      delay_ms(500);
      output_c(255);
      delay_ms(500);
   }   

   output_c(0);
   output_a(0b11111110);
   output_d(0b11111110);

   pr2 = 250;
   ccpr1l = 100;
   ccpr2l = 25;
   t2con = 0b00000100;
   ccp1con = 0b00001100;
   ccp2con = 0b00001100;



   while(true)
   {
      
   }
   
}


