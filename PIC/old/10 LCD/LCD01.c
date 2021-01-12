#include <18F4550.h>
#device adc=8

#include <18Fconfig1)

#use delay(clock=48000000)//Frecuencia de reloj


    #define LCD_RS_PIN      PIN_A1
    #define LCD_RW_PIN      PIN_A2
    #define LCD_ENABLE_PIN  PIN_A3
    #define LCD_DATA4       PIN_D4
    #define LCD_DATA5       PIN_D5
    #define LCD_DATA6       PIN_D6
    #define LCD_DATA7       PIN_D7

    #include "lcd.c"
    
    
    
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
   set_tris_b(0x0F);                   //configura la puerto b parte alta como salidas parte baja entradas
   set_tris_c(0x0);                   //configura la puerto c como salidas
   set_tris_d(0x0);                   //configura la puerto d como salidas
   
   
      lcd_init();                         //Inicializa el lcd
      lcd_pos(0x80);
      printf(lcd_putc,"\fPRUEBA DE LCD PARA LA MATERIA");
      lcd_pos(0xC0);
      printf(lcd_putc,"MICROS PARA LA MATERIA DE ES");
      lcd_pos(0x90);
      printf(lcd_putc,"");
      lcd_pos(0xD0);
      printf(lcd_putc,"");
      while(true)
      {
      }
}


