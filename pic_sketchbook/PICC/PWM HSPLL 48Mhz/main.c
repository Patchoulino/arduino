#include <18F4550.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HSPLL                    //High Speed Crystal/Resonator with PLL enabled
#FUSES PROTECT                //Code not protected from reading
#FUSES BROWNOUT               //No brownout reset
#FUSES BORV20                   //Brownout reset at 2.0V
#FUSES PUT                    //No Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
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
#FUSES ICPRT                    //ICPRT enabled

#use delay(clock=48M)

#define LCD_ENABLE_PIN  PIN_D7                                   
#define LCD_RS_PIN      PIN_D5                                   
#define LCD_RW_PIN      PIN_D6                                
#define LCD_DATA4       PIN_B0                                
#define LCD_DATA5       PIN_B1                                 
#define LCD_DATA6       PIN_B2                                  
#define LCD_DATA7       PIN_B3 

#include <LCD.C>

#define BTNCH PIN_A1
#define BTNUP PIN_A2
#define BTNDN PIN_A3

#define CCP1 PIN_C2
#define CCP2 PIN_C1

   int pwm1 = 100;
   int pwm2 = 100;
   int c = 10;
   
   int i;
   long j;
   
   void pwm();

void main()
{
   set_tris_a(0xFF);
   set_tris_c(0x00);
   
   lcd_init();
   
   lcd_gotoxy(1,1);
   printf(lcd_putc,"PWM Generator");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"Abraham  Aguilar");
   delay_ms(1000);
   lcd_gotoxy(1,1);
   printf(lcd_putc,"                 ");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"                 ");
   
   short var = 0;

    while(true)
    {
      lcd_gotoxy(1,1);
      printf(lcd_putc,"PWM1: %u  x:%u   ",pwm1,var);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"PWM2: %u   ",pwm2);
      
      pwm();
      
      if(input(BTNCH)) 
      {
         var++;
         while(input(BTNCH)){pwm();}
      }
      
      if(input(BTNUP))
      {
         if(var)
         {
            pwm2 = pwm2 + c;
         }
         else
         {
            pwm1 = pwm1 + c;
         }
      }
      
      if(input(BTNDN))
      {
         if(var)
         {
            pwm2 = pwm2 - c;
         }
         else
         {
            pwm1 = pwm1 - c;
         }
      }
      
      if(pwm1>200) pwm1 = 0;
      if(pwm1>100) pwm1 = 100;
      if(pwm2>200) pwm2 = 0;
      if(pwm2>100) pwm2 = 100;
    }
}

void pwm()
{
   
      for(j=0;j<=1000;j++)
      {
         for(i=0;i<=100;i++)
         {
            if(pwm1>=i) output_bit(CCP1,1);
            else        output_bit(CCP1,0);
            if(pwm2>=i) output_bit(CCP2,1); 
            else        output_bit(CCP2,0);
            delay_us(1);
         }
      }
}
