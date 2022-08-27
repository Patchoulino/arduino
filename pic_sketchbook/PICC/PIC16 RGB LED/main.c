#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC                    //Internal RC Osc
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#use delay(int=4000000)

#INCLUDE <STDLIB.H>

#define RED PIN_B0
#define GRN PIN_B1
#define BLU PIN_B2

void main()
{

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   set_tris_b(0x00);
   
   float a,b,c;
   int x,y,z;
   int i;
   long j;
   
   //Inicio Semaforo
   output_bit(RED,0);   output_bit(GRN,1);   output_bit(BLU,0);   delay_ms(3000);
   output_bit(RED,0);   output_bit(GRN,0);   output_bit(BLU,0);   delay_ms(500);
   output_bit(RED,0);   output_bit(GRN,1);   output_bit(BLU,0);   delay_ms(500);
   output_bit(RED,0);   output_bit(GRN,0);   output_bit(BLU,0);   delay_ms(500);
   output_bit(RED,0);   output_bit(GRN,1);   output_bit(BLU,0);   delay_ms(500);
   output_bit(RED,1);   output_bit(GRN,1);   output_bit(BLU,0);   delay_ms(1000);
   output_bit(RED,1);   output_bit(GRN,0);   output_bit(BLU,0);   delay_ms(2000);

    while(true)
    {
    
      j = j + 1;
      if (j == 1000)
      {
         j = 0;
         
   //Inicio Semaforo
   output_bit(RED,0);   output_bit(GRN,1);   output_bit(BLU,0);   delay_ms(3000);
   output_bit(RED,0);   output_bit(GRN,0);   output_bit(BLU,0);   delay_ms(500);
   output_bit(RED,0);   output_bit(GRN,1);   output_bit(BLU,0);   delay_ms(500);
   output_bit(RED,0);   output_bit(GRN,0);   output_bit(BLU,0);   delay_ms(500);
   output_bit(RED,0);   output_bit(GRN,1);   output_bit(BLU,0);   delay_ms(500);
   output_bit(RED,1);   output_bit(GRN,1);   output_bit(BLU,0);   delay_ms(1000);
   output_bit(RED,1);   output_bit(GRN,0);   output_bit(BLU,0);   delay_ms(2000);
   
      }
      
      a = rand();
      b = rand();
      c = rand();
      
      x = (a / 32767) * 255;
      y = (b / 32767) * 255;
      z = (c / 32767) * 255;
      
      if(x > 0) output_high(RED);
      if(y > 0) output_high(GRN);
      if(z > 0) output_high(BLU);
      
      for(i = 0; i < 255; i++)
      {
         if(x < i) output_low(RED);
         if(y < i) output_low(GRN);
         if(z < i) output_low(BLU);
         delay_us(1);
      }
    }
}
