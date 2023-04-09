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

#define LED PIN_D3

   #word ccpr1    = 0xfbe
   #byte ccp1con  = 0xfbd
   #byte t1con    = 0xfcd 
   #byte t3con    = 0xfb1  

   int8 ms = 0;
   int8 sec = 0;
   int8 min = 3;
   int8 hr = 20;
   int8 dec = 0;
    
    #int_ccp1
    void ccp1_isr(void)
    {
       dec++;
        if (dec==4)   //con 10 Genera un tiempo de 0.025 segundos con 40 genera 1 segundo
        {
            ms++;
            if (ms==10)
            {
               sec++;
               ms = 0;
               if (sec==60)
               {
                  min++;
                  sec = 0;
                  if (min==60)
                  {
                     hr++;
                     min = 0;
                     if (hr>23)
                     {
                        hr = 0;
                     }
                  }
               }
               output_toggle(LED);
            }
            dec = 0;
        }  
    }

 // 37500 * 1:8 ccp1con postcaler = 300k
 // 300k * if 40 = 12M = PIC CLK / 4
 
void main()
{
      enable_interrupts(GLOBAL);          //habilito interrupción global
      enable_interrupts(INT_ccp1);        //habilito interrupción de ccp1
      ccpr1 = 37500;                      //tiempo de conteo del ccp1 para 0.1s
      ccp1con = 0b00001011;               //Config del caption compare para usar el T1 como referencia        
      t1con = 0b00110000;                 //Config del timer 1 1:8
      t3con = 0b00000000;                 //Se configura el tiemer 3 para usar el timer 1 en el CCP

    lcd_init();

    bit_set(t1con,0);                     // Enables T1
    
    int x;

    while(true)
    {
      delay_us(1);
      x = (sec / 2) + 1;
      if(x>=18 && x<=33)
      {
         x = x - ((x - 17) * 2);
      }
      if(x>1)
      {
         lcd_gotoxy(x-1,1);
         printf(lcd_putc," ");
      }
      lcd_gotoxy(x,1);
      printf(lcd_putc,"Abraham  Aguilar");
      lcd_gotoxy(4,2);
      printf(lcd_putc,"%u:%u:%u:%u    ",hr,min,sec,ms);
    }
}
