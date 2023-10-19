/*
   PIC PIANO
   
   using 12 buttons each will correspond to a note
   if more than 2 buttons are pressed at the same time
   the program will generate a mixed sound of the 
   buttons pressed
   
   one aditional button will allow the user to switch between octaves
   from 0 to 3, 2 leds will indicate in which octave the user
   currently is located.
*/

#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reads
#FUSES NOBROWNOUT               //No reset when brownout detected
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#byte pcon = 0x0E               //Dirección de pcon

#use delay(int=4M)

#include <TONES.C>

#define BTNC  PIN_A5
#define BTNDB PIN_A4
#define BTND  PIN_A3
#define BTNEB PIN_A2
#define BTNE  PIN_A1
#define BTNF  PIN_A0
#define BTNGB PIN_A7
#define BTNG  PIN_A6
#define BTNAB PIN_B7
#define BTNA  PIN_B6
#define BTNBB PIN_B5
#define BTNB  PIN_B4

#define BTN   PIN_B3

#define LEDH  PIN_B2
#define LEDL  PIN_B1

unsigned long note = 0;
unsigned int duration = 100;
unsigned int octave = 1;
unsigned int btn_pressed = 0;

void main()
{

   //bit_clear(pcon,3);   //INTOSC = 48Khz
   bit_set(pcon,3);       //INTOSC = 4Mhz  
   
   //setup_oscillator(OSC_48KHZ);   //OSC_48KHZ = 0   0b0000
                                    //OSC_4MHZ = 8    0b1000

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   set_tris_a(0xFF);
   set_tris_b(0b11111000);
   
   output_a(0x00);
   output_b(0);

    while(true)
    {
    
      note = 0;
      btn_pressed = 0;
      
      if(input(BTNC))    
      {
         note = note + C_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNDB))  
      {  
         note = note + Db_NOTE[3];
         btn_pressed++;
      }
      if(input(BTND))    
      {
         note = note + D_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNEB))  
      {
         note = note + Eb_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNE))  
      {
         note = note + E_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNF))   
      {
         note = note + F_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNGB)) 
      {
         note = note + Gb_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNG)) 
      {  
         note = note + G_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNAB)) 
      {
         note = note + Ab_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNA))  
      {
         note = note + A_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNBB)) 
      {
         note = note + Bb_NOTE[3];
         btn_pressed++;
      }
      if(input(BTNB))
      {
         note = note + B_NOTE[3];
         btn_pressed++;
      }
      
      if(btn_pressed != 0)
      {
         note = note / btn_pressed;    // Calcula el promedio dependiendo
      }                                // de la cantidad de botones presionados
      
      if(input(BTN))
      {
         while(input(BTN))
         {
            delay_ms(1);
         }
         octave++;
         if(octave == 4) octave = 0;
      }
      
      switch(octave)
      {
         case 0:
            note = note / 8;
            output_bit(LEDL, 0);
            output_bit(LEDH, 0);
            break;
         case 1:
            note = note / 4;
            output_bit(LEDL, 1);
            output_bit(LEDH, 0);
            break;
         case 2:
            note = note / 2;
            output_bit(LEDL, 0);
            output_bit(LEDH, 1);
            break;
         case 3:
            note = note / 1;
            output_bit(LEDL, 1);
            output_bit(LEDH, 1);
            break;
      }
      
      if(note != 0)
      {
         generate_tone(note, duration);
      }
      else
      {
         delay_ms(duration);
      }
 
    }
}

