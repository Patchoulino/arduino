#include <18F4550.h>
#device adc=8

// Pass strings through functions
#device PASS_STRINGS = IN_RAM

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HSPLL                    //High Speed Crystal/Resonator with PLL enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BORV20                   //Brownout reset at 2.0V
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES NOIESO                   //Internal External Switch Over mode disabled
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled
#FUSES PBADEN                   //PORTB pins are configured as analog input channels on RESET
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads
#FUSES NOCPB                    //No Boot Block code protection
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES LPT1OSC                  //Timer1 configured for low-power operation
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES PLL5                     //Divide By 5(20MHz oscillator input)
#FUSES CPUDIV1                  //No System Clock Postscaler
#FUSES USBDIV                   //USB clock source comes from PLL divide by 2
#FUSES NOVREGEN                 //USB voltage regulator disabled

// Crystal = 20M; PLL5 + HSPLL 
#use delay(clock=48M)

// LCD PINS
#define LCD_ENABLE_PIN  PIN_D7                                   
#define LCD_RS_PIN      PIN_D5                                   
#define LCD_RW_PIN      PIN_D6                                
#define LCD_DATA4       PIN_B0                                
#define LCD_DATA5       PIN_B1                                 
#define LCD_DATA6       PIN_B2                                  
#define LCD_DATA7       PIN_B3 

#include <LCD.C>

// DS1302 PINS
#define RTC_RST         PIN_D1
#define RTC_IO          PIN_D0
#define RTC_SCLK        PIN_C2

#include <DS1302.C>

void main()
{   
   lcd_init();
   
   lcd_gotoxy(1,1);
   printf(lcd_putc,"      RTC       ");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"Abraham  Aguilar");
   delay_ms(3000);
   lcd_gotoxy(1,1);
   printf(lcd_putc,"                ");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"                ");

   rtc_init();
   
   int day = 2;
   int mth = 3;
   int year = 15;
   int dow = 1;      //no se que es esto
   int hour = 5;
   int min = 15;
   int sec;
   
   //rtc_set_datetime(day,mth,year,dow,hour,min);
   

   while(true)
   {
      
      lcd_gotoxy(1,1);
      printf(lcd_putc,"   %u/%u/20%u/%u    ",day,mth,year,dow);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"     %u:%u:%u      ",hour,min,sec);
   
      rtc_get_date(day,mth,year,dow);
      rtc_get_time(hour,min,sec);
      
      delay_ms(1);
   
   }
}
