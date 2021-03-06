#include <18F4550.h>
#device adc=8

#FUSES NOWDT                     //No Watch Dog Timer
#FUSES WDT128                    //Watch Dog Timer uses 1:128 Postscale
#FUSES HSPLL        //cambio para frec      //External clock
#FUSES PROTECT                 //Code not protected from reading
#FUSES NOBROWNOUT                //No brownout reset
#FUSES BORV20                    //Brownout reset at 2.0V
#FUSES NOPUT                     //No Power Up Timer
#FUSES CPD                     //No EE protection
#FUSES STVREN                    //Stack full/underflow will cause reset
#FUSES NODEBUG                   //No Debug mode for ICD
#FUSES NOLVP                     //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                     //Program memory not write protected
#FUSES NOWRTD                    //Data EEPROM not write protected
#FUSES NOIESO                      //Internal External Switch Over mode enabled
#FUSES NOFCMEN                     //Fail-safe clock monitor enabled
#FUSES PBADEN                    //PORTB pins are configured as analog input channels on RESET
#FUSES NOWRTC                    //configuration not registers write protected
#FUSES NOWRTB                    //Boot block not write protected
#FUSES NOEBTR                    //Memory not protected from table reads
#FUSES NOEBTRB                   //Boot block not protected from table reads
#FUSES NOCPB                     //No Boot Block code protection
#FUSES MCLR                      //Master Clear pin enabled
#FUSES LPT1OSC                   //Timer1 configured for low-power operation
#FUSES NOXINST                   //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES PLL1                //cambio para frec   //Divide By 12(48MHz oscillator input)
#FUSES CPUDIV1             //cambio para frec //System Clock by 4
#FUSES USBDIV                    //USB clock source comes from PLL divide by 2
#FUSES VREGEN                    //USB voltage regulator enabled
//#FUSES ICPRT                     //ICPRT enabled


    #use delay(clock=48000000)//Frecuencia de reloj


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
   set_tris_c(0x0);                   //configura la puerto c como salidas
   set_tris_d(0x0);                   //configura la puerto d como salidas

   // TODO: USER CODE!!
   int i;
   
   
   for (i=1;i<3;i++)
   {
      output_c(0);
      delay_ms(500);
      output_c(255);
      delay_ms(500);
   }   

   output_c(0);
   output_d(0xc0); // display 0 

   int j;
   while(true)
   {
      j=0b11111110;
      for (i=1;i<=6;i++)
      {
         output_a(j); // seleccion del numero de display con logica negativa
         delay_ms(1);
         j=j<<1|1;
      }
   }
   
}

