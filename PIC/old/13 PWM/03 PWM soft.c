#include <18F4550.h>
#device adc=8
#include <18Fconfig1.h>



#use delay(clock=48000000)//Frecuencia de reloj

#word corr     = 0x200

#bit  corr0    = corr.0
#bit  corr1    = corr.1
#bit  corr2    = corr.2
#bit  corr3    = corr.3
#bit  corr4    = corr.4
#bit  corr5    = corr.5
#bit  corr6    = corr.6
#bit  corr7    = corr.7
#bit  corr8    = corr.8
#bit  corr9    = corr.9
#bit  corr10   = corr.10
#bit  corr11   = corr.11
#bit  corr12   = corr.12
#bit  corr13   = corr.13
#bit  corr14   = corr.14
#bit  corr15   = corr.15

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
   int8 pwm[16];
   
   
   for (i=1;i<3;i++)
   {
      output_c(255);
      delay_ms(500);
      output_c(0);
      delay_ms(500);
   }   
         for (i=0;i<16;i++)
         {
            pwm[i] = 100;
         }

   corr = 1;
   int16 cont = 0;
   int32 cont2 = 0;
   output_c(0);
   output_b(0);
   output_d(0);
   
   while(true)
   {
     cont++;
     cont2++;
     if (cont == pwm[0]) output_bit(PIN_B0,1);
     if (cont == pwm[1]) output_bit(PIN_B1,1);
     if (cont == pwm[2]) output_bit(PIN_B2,1);
     if (cont == pwm[3]) output_bit(PIN_B3,1);
     if (cont == pwm[4]) output_bit(PIN_B4,1);
     if (cont == pwm[5]) output_bit(PIN_B5,1);
     if (cont == pwm[6]) output_bit(PIN_B6,1);
     if (cont == pwm[7]) output_bit(PIN_B7,1);
     if (cont == pwm[8]) output_bit(PIN_C7,1);
     if (cont == pwm[9]) output_bit(PIN_C6,1);
     if (cont == pwm[10]) output_bit(PIN_D5,1);
     if (cont == pwm[11]) output_bit(PIN_D4,1);
     if (cont == pwm[12]) output_bit(PIN_D3,1);
     if (cont == pwm[13]) output_bit(PIN_C2,1);
     if (cont == pwm[14]) output_bit(PIN_C1,1);
     if (cont == pwm[15]) output_bit(PIN_C0,1);
     if (cont >= 100) 
     {
         cont = 0;
         output_c(0);
         output_b(0);
         output_d(0);
     }
     if (cont2 >= 4000) 
     {
         cont2 = 0;
//         output_c(corr);
         if (corr0 == 1) pwm[0]=50;
         if (corr1 == 1) pwm[1]=50;
         if (corr2 == 1) pwm[2]=50;
         if (corr3 == 1) pwm[3]=50;
         if (corr4 == 1) pwm[4]=50;
         if (corr5 == 1) pwm[5]=50;
         if (corr6 == 1) pwm[6]=50;
         if (corr7 == 1) pwm[7]=50;
         if (corr8 == 1) pwm[8]=50;
         if (corr9 == 1) pwm[9]=50;
         if (corr10 == 1) pwm[10]=50;
         if (corr11 == 1) pwm[11]=50;
         if (corr12 == 1) pwm[12]=50;
         if (corr13 == 1) pwm[13]=50;
         if (corr14 == 1) pwm[14]=50;
         if (corr15 == 1) pwm[15]=50;
         corr = corr << 1;
         for (i=0;i<16;i++)
         {
            pwm[i] = pwm[i] + 10;
         }
     }
     if (corr == 0) corr = 1;
     delay_us(10); 
      
      
      
   }
   
}



