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
//#FUSES ICPRT                    //ICPRT enabled

#use delay(clock=48M)

#define LCD_ENABLE_PIN  PIN_D7                                   
#define LCD_RS_PIN      PIN_D5                                   
#define LCD_RW_PIN      PIN_D6                                
#define LCD_DATA4       PIN_B0                                
#define LCD_DATA5       PIN_B1                                 
#define LCD_DATA6       PIN_B2                                  
#define LCD_DATA7       PIN_B3 
#include <LCD.C>

long get_freq(void);
#define SIGNAL PIN_A0

void filter(char *color);  
#define S3 PIN_A3
#define S2 PIN_A2

   #define RED PIN_D1
   #define GRN PIN_D3
   #define BLU PIN_D2
   
const long WHITE_C = 7420;
const long RED_C = 2660;
const long GREEN_C = 1830;
const long BLUE_C = 2380;
const long YELLOW_C = 4540;
const long BLACK_C = 1140;
const long BLANK_C = 440;

const long WHITE_R = 2520;
const long RED_R = 1740;
const long GREEN_R = 500;
const long BLUE_R = 300;
const long YELLOW_R = 2240;
const long BLACK_R = 400;
const long BLANK_R = 200;

const long WHITE_G = 2200;
const long RED_G = 560;
const long GREEN_G = 740;
const long BLUE_G = 533;
const long YELLOW_G = 1500;
const long BLACK_G = 400;
const long BLANK_G = 140;

const long WHITE_B = 2820;
const long RED_B = 680;
const long GREEN_B = 740;
const long BLUE_B = 1366;
const long YELLOW_B = 940;
const long BLACK_B = 460;
const long BLANK_B = 200;

void main()
{   
   lcd_init();
   
   lcd_gotoxy(1,1);
   printf(lcd_putc,"  Color Sensor");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"Abraham  Aguilar");
   delay_ms(1000);
   lcd_gotoxy(1,1);
   printf(lcd_putc,"                ");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"                ");

   long x = 0;

   while(true)
   {
   
      //delay_ms(500);
    
      x = get_freq();   //Freq
    
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Freq: %lu       ",x);
      lcd_gotoxy(1,2);
      
      if(x > WHITE_C - ((WHITE_C - YELLOW_C)/2)) 
      {
         printf(lcd_putc,"Color: White    ");
         output_bit(RED,1);         output_bit(GRN,1);         output_bit(BLU,1);
      }
      if(x > YELLOW_C - ((YELLOW_C - RED_C)/2) && x < YELLOW_C + ((WHITE_C - YELLOW_C)/2))   
      {
         printf(lcd_putc,"Color: Yellow    ");
         output_bit(RED,1);         output_bit(GRN,1);         output_bit(BLU,0);
      }
      if(x > RED_C - ((RED_C - BLUE_C)/2) && x < RED_C + ((YELLOW_C - RED_C)/2))   
      {
         printf(lcd_putc,"Color: Red    ");
         output_bit(RED,1);         output_bit(GRN,0);         output_bit(BLU,0);
      }
      if(x > BLUE_C - ((BLUE_C - GREEN_C)/2) && x < BLUE_C + ((RED_C - BLUE_C)/2))   
      {
         printf(lcd_putc,"Color: Blue    ");
         output_bit(RED,0);         output_bit(GRN,0);         output_bit(BLU,1);
      }
      if(x > GREEN_C - ((GREEN_C - BLACK_C)/2) && x < GREEN_C + ((BLUE_C - GREEN_C)/2))   
      {
         printf(lcd_putc,"Color: Green    ");
         output_bit(RED,0);         output_bit(GRN,1);         output_bit(BLU,0);
      }
      if(x > BLACK_C - ((BLACK_C - BLANK_C)/2) && x < BLACK_C + ((GREEN_C - BLACK_C)/2))  
      {
         printf(lcd_putc,"Color: Black    ");
         output_bit(RED,0);         output_bit(GRN,0);         output_bit(BLU,0);
      }
      if(x < BLANK_C + ((BLACK_C - BLACK_C)/2))  
      {
         printf(lcd_putc,"Color: NULL    ");
         output_bit(RED,0);         output_bit(GRN,0);         output_bit(BLU,0);
      }
         
   }
}

long get_freq()
{

   long c = 0;
   long freq;

   while(input(SIGNAL) == true){}
   while(input(SIGNAL) == false){}
   
   if(input(SIGNAL))
   {
      while(input(SIGNAL))
      {
         delay_us(1);
         c++;
      }
   }
   
   freq = 297619 / c;
   return freq;
   
}

void filter(char *color)
{ 
   switch(color)
   {
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
      case "CLEAR":
         output_bit(S2,1);
         output_bit(S3,0);
         break;
      case "null":
         break;
   }
}

