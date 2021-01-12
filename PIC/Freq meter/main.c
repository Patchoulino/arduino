#include <18F4550.h>
#device adc=8
#include <18Fmap.h>
#include <18Fconfig1.h>

// Pass strings through functions
#device PASS_STRINGS = IN_RAM

#use delay(clock=48M)//Frecuencia de reloj

#define LCD_ENABLE_PIN  PIN_D7                                   
#define LCD_RS_PIN      PIN_D5                                   
#define LCD_RW_PIN      PIN_D6                                
#define LCD_DATA4       PIN_B0                                
#define LCD_DATA5       PIN_B1                                 
#define LCD_DATA6       PIN_B2                                  
#define LCD_DATA7       PIN_B3 

#include "lcd.c"
    
int1 bandera;
    
int16 time1;
float clear,red,green,blue;

    #int_ccp1
    void ccp1_isr(void)
    {
            time1 = tmr1;
            tmr1 = 0;
            bandera = 1;
    }

void filter(char *color);
#define S3 PIN_B4
#define S2 PIN_B5

#define REE PIN_D1
#define GRN PIN_D3
#define BLU PIN_D2
    
const long RANGE = 300;

const long WHITE_C = 5900;
const long RED_C = 2200;
const long GREEN_C = 1700;
const long BLUE_C = 1933;
const long YELLOW_C = 3866;
const long BLACK_C = 1300;
const long BLANK_C = 333;

const long WHITE_R = 2500;
const long RED_R = 1933;
const long GREEN_R = 566;
const long BLUE_R = 333;
const long YELLOW_R = 2466;
const long BLACK_R = 566;
const long BLANK_R = 133;

const long WHITE_G = 2266;
const long RED_G = 566;
const long GREEN_G = 800;
const long BLUE_G = 633;
const long YELLOW_G = 1666;
const long BLACK_G = 500;
const long BLANK_G = 100;

const long WHITE_B = 3000;
const long RED_B = 700;
const long GREEN_B = 833;
const long BLUE_B = 1600;
const long YELLOW_B = 1033;
const long BLACK_B = 633;
const long BLANK_B = 133;
    
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
   
      enable_interrupts(GLOBAL);          //habilito interrupción global
      enable_interrupts(int_ccp1);        //habilito interrupción de ccp1
      ccpr1 = 45000;                      //tiempo de conteo del ccp1 para 0.1s
      ccp1con = 0b00001011;               //Config del caption compare para usar el T1 como referencia        
      t3con = 0b01111001;                 //Se configura el tiemer 3 para usar el timer 1 en el CCP
      
   delay_ms(300);
   lcd_init();                         //Inicializa el lcd
   t1con = 0b10000011;

   printf(lcd_putc,"\f");
   
   bandera = 0;
   
   set_tris_b(0x00);
   
   while(true)
   {
      
      filter("CLEAR");  clear = time1;    clear = clear / 0.03;
      filter("RED");    red = time1;      red = red / 0.03;
      filter("GREEN");  green = time1;    green = green / 0.03;
      filter("BLUE");   blue = time1;     blue = blue / 0.03;
      
      lcd_gotoxy(1,1);
      printf(lcd_putc,"R:%4.0f G:%4.0f    ",red,green);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"B:%4.0f C:%4.0f    ",blue,clear);
      
      if(clear > WHITE_C - RANGE && clear < WHITE_C + RANGE) 
      {
         if(red > WHITE_R - RANGE && red < WHITE_R + RANGE) 
         {
            if(green > WHITE_G - RANGE && green < WHITE_G + RANGE) 
            {
               if(blue > WHITE_B - RANGE && blue < WHITE_B + RANGE) 
               {
                  printf(lcd_putc,"Color: White    ");
                  output_bit(REE,1);         output_bit(GRN,1);         output_bit(BLU,1);
               }
            }
         }
      }
      if(clear > YELLOW_C - RANGE && clear < YELLOW_C + RANGE) 
      {
         if(red > YELLOW_R - RANGE && red < YELLOW_R + RANGE) 
         {
            if(green > YELLOW_G - RANGE && green < YELLOW_G + RANGE) 
            {
               if(blue > YELLOW_B - RANGE && blue < YELLOW_B + RANGE) 
               {
                  printf(lcd_putc,"Color: Yellow    ");
                  output_bit(REE,1);         output_bit(GRN,1);         output_bit(BLU,0);
               }
            }
         }
      }
      if(clear > RED_C - RANGE && clear < RED_C + RANGE) 
      {
         if(red > RED_R - RANGE && red < RED_R + RANGE) 
         {
            if(green > RED_G - RANGE && green < RED_G + RANGE) 
            {
               if(blue > RED_B - RANGE && blue < RED_B + RANGE) 
               {
                  printf(lcd_putc,"Color: Red    ");
                  output_bit(REE,1);         output_bit(GRN,0);         output_bit(BLU,0);
               }
            }
         }
      }
      if(clear > GREEN_C - RANGE && clear < GREEN_C + RANGE) 
      {
         if(red > GREEN_R - RANGE && red < GREEN_R + RANGE) 
         {
            if(green > GREEN_G - RANGE && green < GREEN_G + RANGE) 
            {
               if(blue > GREEN_B - RANGE && blue < GREEN_B + RANGE) 
               {
                  printf(lcd_putc,"Color: Green    ");
                  output_bit(REE,0);         output_bit(GRN,1);         output_bit(BLU,0);
               }
            }
         }
      }
      if(clear > BLUE_C - RANGE && clear < BLUE_C + RANGE) 
      {
         if(red > BLUE_R - RANGE && red < BLUE_R + RANGE) 
         {
            if(green > BLUE_G - RANGE && green < BLUE_G + RANGE) 
            {
               if(blue > BLUE_B - RANGE && blue < BLUE_B + RANGE) 
               {
                  printf(lcd_putc,"Color: Blue    ");
                  output_bit(REE,0);         output_bit(GRN,0);         output_bit(BLU,1);
               }
            }
         }
      }
      if(clear > BLACK_C - RANGE && clear < BLACK_C + RANGE) 
      {
         if(red > BLACK_R - RANGE && red < BLACK_R + RANGE) 
         {
            if(green > BLACK_G - RANGE && green < BLACK_G + RANGE) 
            {
               if(blue > BLACK_B - RANGE && blue < BLACK_B + RANGE) 
               {
                  printf(lcd_putc,"Color: Black    ");
                  output_bit(REE,0);         output_bit(GRN,0);         output_bit(BLU,0);
               }
            }
         }
      }
      if(clear > BLANK_C - RANGE && clear < BLANK_C + RANGE) 
      {
         if(red > BLANK_R - RANGE && red < BLANK_R + RANGE) 
         {
            if(green > BLANK_G - RANGE && green < BLANK_G + RANGE) 
            {
               if(blue > BLANK_B - RANGE && blue < BLANK_B + RANGE) 
               {
                  printf(lcd_putc,"Color:            ");
                  output_bit(REE,0);         output_bit(GRN,0);         output_bit(BLU,0);
               }
            }
         }
      }
      
   }
   
}

void filter(char *color)
{ 
   bit_clear(t1con,0);
   bit_clear(t3con,0);
   //bandera = 0;
   tmr1 = 0;
   
   switch(color)
   {
      case "CLEAR":
         output_bit(S2,1);
         output_bit(S3,0);
         break;
      case "RED":
         output_bit(S2,0);
         output_bit(S3,0);
         break;
      case "GREEN":
         output_bit(S2,1);
         output_bit(S3,1);
         break;
      case "BLUE":
         output_bit(S2,0);
         output_bit(S3,1);
         break;
      case "NULL":
         break;
   }
   
   delay_ms(10);
   bit_set(t1con,0);
   bit_set(t3con,0);
   while(bandera==0){}  
   bandera = 0;
   
}
