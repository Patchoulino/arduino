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

float pwm_c;
long pwm_r,pwm_g,pwm_b;

    #int_ccp1
    void ccp1_isr(void)
    {
            time1 = tmr1;
            tmr1 = 0;
            bandera = 1;
    
    }
void pwm(void);

const long RES = 100;

void filter(char *color);

#define S3 PIN_B4
#define S2 PIN_B5

#define REE PIN_D1
#define GRN PIN_D3
#define BLU PIN_D2

const long WHITE_C = 5900;
const long BLANK_C = 333;

const long WHITE_R = 2500;
const long BLANK_R = 133;

const long WHITE_G = 2266;
const long BLANK_G = 100;

const long WHITE_B = 3000;
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
      
      pwm_c = (clear - BLANK_C)/(WHITE_C - BLANK_C);
      pwm_r = ((red - BLANK_R)/(WHITE_R - BLANK_R) * RES);
      pwm_g = ((green - BLANK_G)/(WHITE_G - BLANK_G) * RES);
      pwm_b = ((blue - BLANK_B)/(WHITE_B - BLANK_B) * RES);
      
      lcd_gotoxy(1,1);
      printf(lcd_putc,"R:%5lu G:%4lu    ",pwm_r,pwm_g);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"B:%5lu C:%1.3f    ",pwm_b,pwm_c);
      
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
   
   pwm();
   bit_set(t1con,0);
   bit_set(t3con,0);
   while(bandera==0){}  
   bandera = 0;
   
}

void pwm(void)
{
   if(pwm_r > 0) output_bit(REE,1);
   if(pwm_g > 0) output_bit(GRN,1);
   if(pwm_b > 0) output_bit(BLU,1);
   
   long pwm_i;
   
   for(pwm_i = 1; pwm_i <= RES; pwm_i++)
   {
      if(pwm_r <= pwm_i) output_bit(REE,0);
      if(pwm_g <= pwm_i) output_bit(GRN,0);
      if(pwm_b <= pwm_i) output_bit(BLU,0);
      delay_us(1);
   }
   
   output_bit(REE,0);
   output_bit(GRN,0);
   output_bit(BLU,0);
}
