#include <18F4550.h>
#device adc=8
// Pass strings through functions
#device PASS_STRINGS = IN_RAM

//*********************** Fusibles y Configuraci�n del PIC ****************
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPROTECT                  //Code protected from reads
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BORV42                   //Brownout reset at 4.2V
#FUSES PUT                      //Power Up Timer
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
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOLPT1OSC                //Timer1 configured for higher power operation
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES PLL5                     //Divide By 5(20MHz oscillator input)
#FUSES CPUDIV1                  //No System Clock Postscaler
#FUSES USBDIV                   //USB clock source comes from PLL divide by 2
#FUSES VREGEN                   //USB voltage regulator enabled
#FUSES ICPRT                    //ICPRT enabled

#use delay(clock=20000000,RESTART_WDT)

//*********************** Librerias ****************
#include <usb_cdc.h>
#include <usb_desc_cdc.h>

//*********************** Declaracion de pines ****************
// LED Control PINS
#define LED PIN_A4

//*********************** Funciones y Subrutinas ****************
void ports_init()
{
   set_tris_a(0x00);
   set_tris_b(0x00);          //0b11110000 = 255-1-2-4-8= 240 = 0xF0
   set_tris_c(0x00);
   set_tris_d(0x00);          //0b00000000 = 0 = 0x00
   set_tris_e(0x00);
   
   output_a(0x00); 
   output_b(0x00);            //Inicializamos pines apagados
   output_c(0x00);
   output_d(0x00);
   output_e(0x00);
}
//*********************** Variables y Constantes ****************
char comando;                          // Serial Communication Command

// short       = int1            = 0 to 1
// char        = unsigned int8   = 0 to 255
// int         = int8            = 0 to 255      -128 to 127
// long        = int16           = 0 to 65535   -32768 to 32767
// long long   = int32           = 0 to 4294967295
// float       = float32         = -1.5 x 10^45  to  3.4 x 10^38

void main()
{
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   ports_init();
   
   int i;
   for(i = 0; i < 3; i++)
   {
      output_bit(LED,1);
      delay_ms(500);
      output_bit(LED,0);
      delay_ms(500);
   }
   
   while(True)
   {
      
      if(usb_enumerated())
      {
         usb_task();
         if(usb_cdc_kbhit())
         {
            comando = usb_cdc_getc();
            usb_cdc_putc(comando);
            switch(comando)
            {
               case '@':
                  char var = 33;
                  do{
                     printf(usb_cdc_putc,"Char: %c | Int: %u | Hex: %X",var,var,var);
                     usb_cdc_putc(10);
                     usb_cdc_putc(13);
                     var++;
                  }while(var != 127);
                  break;
               case 'e':
               case 'E':
                  output_bit(LED,1);
                  break;
               case 'a':
               case 'A':
                  output_bit(LED,0);
                  break;
               case 't':
               case 'T':
                  output_toggle(LED);
                  break;
               case '1':
                  usb_cdc_putc('@');
                  break;
               case '2':
                  usb_cdc_putc(64);
                  break;
               case '3':
                  var = 64;
                  printf(usb_cdc_putc,"Char: %c | Int: %u | Hex: %X",var,var,var);
                  break;
            }
         }
      }
      else
      {
         output_bit(LED,0);
         usb_cdc_init();
         usb_init();
         usb_task();
         usb_wait_for_enumeration();
         output_bit(LED,1);
      }
   }
}

