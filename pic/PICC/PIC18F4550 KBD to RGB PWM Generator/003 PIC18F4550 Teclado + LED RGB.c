#include <18F4550.h>
#device adc=8

//*********************** Fusibles y Configuración del PIC ****************
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES PROTECT                  //Code protected from reads
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

//*********************** Declaracion de pines ****************
// Keypad PINS
#define R1 PIN_B7
#define R2 PIN_B6
#define R3 PIN_B5
#define R4 PIN_B4
#define C1 PIN_B3
#define C2 PIN_B2
#define C3 PIN_B1
#define C4 PIN_B0
// Motor Control PINS
#define R PIN_D0
#define B PIN_D1
#define G PIN_D2

//*********************** Funciones y Subrutinas ****************
void ports_init()
{
   set_tris_b(0xF0);          //0b11110000 = 255-1-2-4-8= 240 = 0xF0
   set_tris_d(0x00);          //0b00000000 = 0 = 0x00
   
   output_b(0x00);            //Inicializamos pines apagados
   output_d(0x00);
}
void Led_Routine(void);

//*********************** Variables y Constantes ****************
short Shut_Down = 0;
short Keypad_Enabled = 1; 

short Red = 0;                     // Used along with Motor_X_Pos
short Green = 0;                     // to update de position of each
short Blue = 0;                     // motor.           
int X = 0;                          
int Red_X = 0;                   // Motor_X = Enable T/F
int Green_X = 0;                   // Motor_X_Pos = Motor_Pos
int Blue_x = 0;
const int step = 1;
                                       // Command Variables
char key;                              // Keyboard Variable

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
   
   while(TRUE)
   {
      if (Keypad_Enabled == 1)
      {
         output_bit(C1,1); output_bit(C2,0); output_bit(C3,0); output_bit(C4,0);
         if(input(R1)) key='1'; if(input(R2)) key='4'; if(input(R3)) key='7'; if(input(R4)) key='-';
         output_bit(C1,0); output_bit(C2,1); output_bit(C3,0); output_bit(C4,0);
         if(input(R1)) key='2'; if(input(R2)) key='5'; if(input(R3)) key='8'; if(input(R4)) key='0';
         output_bit(C1,0); output_bit(C2,0); output_bit(C3,1); output_bit(C4,0);
         if(input(R1)) key='3'; if(input(R2)) key='6'; if(input(R3)) key='9'; if(input(R4)) key='+';
         output_bit(C1,0); output_bit(C2,0); output_bit(C3,0); output_bit(C4,1);
         if(input(R1)) key='A'; if(input(R2)) key='B'; if(input(R3)) key='C'; if(input(R4)) key='D';
         
         switch (key)
         {
            case '0':
               X = 0;
               break;
            case '1':
               X = 11;
               break;
            case '2':
               X = 22;
               break;
            case '3':
               X = 33;
               break;
            case '4':
               X = 44;
               break;
            case '5':
               X = 55;
               break;
            case '6':
               X = 66;
               break;
            case '7':
               X = 77;
               break;
            case '8':
               X = 88;
               break;
            case '9':
               X = 100;
               break;
            case '+':
               X = X + step;
               break;
            case '-':
               X = X - step;
               break;
            case 'A':
               Red = 1;
               Green = 0;
               Blue = 0;
               X = Red_X;
               break;
            case 'B':
               Green = 1;
               Red = 0;
               Blue = 0;
               X = Green_X;
               break;
            case 'C':
               Blue = 1;
               Red = 0;
               Green = 0;
               X = Blue_X;
               break;
         }
      }
      
      key = ' ';
      if (X > 200) X = 0;
      if (X > 100) X = 100;
      if (Red) Red_X = X;
      if (Green) Green_X = X;
      if (Blue) Blue_X = X;
      
      if(Shut_down)
      {
         Led_Routine();
      }
      else
      {
         int i;
         for(i=0;i<=99;i++) Led_Routine();
      }
   }
}

void Led_Routine()                // 50Hz signal
{                                   // 20ms delay   x5=100ms  x50=1s

   if(Red_X > 0)   output_bit(R,1);
   if(Green_X > 0) output_bit(G,1);
   if(Blue_X > 0)  output_bit(B,1);
   
   int i;
   
   for(i=0;i<=99;i++)
   {
       if(Red_X == i) output_bit(R,0);
       if(Green_X == i) output_bit(G,0);
       if(Blue_X == i) output_bit(B,0);
       delay_us(10);
   }
}
