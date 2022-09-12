#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES XT                       //Crystal osc <= 4mhz for PCM/PCH , 3mhz to 10 mhz for PCD
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected

#use delay(clock=4000000)

// Librerias y sus Define

#define LCD_ENABLE_PIN  PIN_B0                                  
#define LCD_RS_PIN      PIN_B1                                    
#define LCD_RW_PIN      PIN_B2                                   
#define LCD_DATA4       PIN_B4                                   
#define LCD_DATA5       PIN_B5                                  
#define LCD_DATA6       PIN_B6                                   
#define LCD_DATA7       PIN_B7  

#include <LCD.C>

// Funciones y Subrutinas

int kbd_getc(void);

// Variables

int c;

// Etiquetas

#define F1 PIN_D0
#define F2 PIN_D1
#define F3 PIN_D2
#define F4 PIN_D3
#define C1 PIN_D4
#define C2 PIN_D5
#define C3 PIN_D6
#define C4 PIN_D7

#define Door PIN_C0
#define Alarm PIN_C1

void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   
   lcd_init();

    while(true)
    {
      lcd_putc("\f");
      lcd_putc("Hola Mundo");
      lcd_gotoxy(1,2);
      lcd_putc("Mecatronica");
      
      delay_ms(2500);
      
      lcd_putc("\f");
      
      lcd_gotoxy(1,1);
      int i;
      
      long pass = 369;
      long input = 0;
      
      for(i = 1; i <= 3; i++)
      {
             
         while(c == 20)
         {
            c = kbd_getc();
         }
         
         printf(lcd_putc,"%u",c);
         
         if(i == 1)  input = c * 100;
         if(i == 2)  input = c * 10;
         if(i == 3)  input = c;
         
      }
      
      lcd_gotoxy(1,2);
      
      if(input == pass)
      {
         printf(lcd_putc,"Correcto!");
         output_bit(Door,1);
         delay_ms(30000);
      }
      else
      {
         printf(lcd_putc,"Incorrecto");
         output_bit(Alarm,1);
         delay_ms(60000);
      }
      
      output_bit(Door,0);
      output_bit(Alarm,0);
      
    }

}

int kbd_getc(void)
{
   c = 20;
   
   output_bit(F4,0);
   output_bit(F1,1);
   if(input(C1)) c = 7;
   if(input(C2)) c = 8;
   if(input(C3)) c = 9;
   delay_ms(100);
   
   output_bit(F1,0);
   output_bit(F2,1);
   if(input(C1)) c = 4;
   if(input(C2)) c = 5;
   if(input(C3)) c = 6;
   delay_ms(100);
   
   output_bit(F2,0);
   output_bit(F3,1);
   if(input(C1)) c = 1;
   if(input(C2)) c = 2;
   if(input(C3)) c = 3;
   delay_ms(100);
   
   output_bit(F3,0);
   output_bit(F4,1);
   if(input(C2)) c = 0;
   delay_ms(100);
   
   return c;
}
