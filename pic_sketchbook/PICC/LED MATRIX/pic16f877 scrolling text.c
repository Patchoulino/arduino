#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected

#use delay(clock=20M)

#byte PB = 0x06
#bit PB0 = PB.0
#bit PB1 = PB.1
#bit PB2 = PB.2
#bit PB3 = PB.3
#bit PB4 = PB.4
#bit PB5 = PB.5
#bit PB6 = PB.6
#bit PB7 = PB.7

//*********************** Librerias ****************
//#include <usb_cdc.h>
//#include <usb_desc_cdc.h>
#include <math.h>

//*********************** Declaracion de pines ****************

// Led Matrix Defines
#define C1 PIN_C5
#define C2 PIN_C4
#define C3 PIN_D3
#define C4 PIN_D2
#define C5 PIN_D1
#define C6 PIN_D0
#define C7 PIN_C3
#define C8 PIN_C2
/*
#define F1 PIN_B0
#define F2 PIN_B1
#define F3 PIN_B2
#define F4 PIN_B3
#define F5 PIN_B4
#define F6 PIN_B5
#define F7 PIN_B6
#define F8 PIN_B7*/

#define BTN PIN_A3
                          // 9x2 + 5xN
char message[]        =  {0x0C,0x1E,0x3E,0x7C,0x7C,0x3E,0x1E,0x0C, // shape_heart
                          0x00,0x02,0x7E,0x02,0x00, // T
                          0x30,0x68,0x58,0x10,0x00, // e
                          0x00,0x00,0x00,0x00,0x00, //  
                          0x30,0x48,0x28,0x78,0x00, // a
                          0x78,0x10,0x18,0x70,0x00, // m
                          0x30,0x48,0x48,0x30,0x00, // o
                          0x0C,0x1E,0x3E,0x7C,0x7C,0x3E,0x1E,0x0C,0x00}; // shape_heart
                          
char shape_empty[8]           = {0b00000000,
                                 0b00000000,
                                 0b00000000,
                                 0b00000000,
                                 0b00000000,
                                 0b00000000,
                                 0b00000000,
                                 0b00000000};
                                 
char shape_pokeball[8]        = {0x3C,0x4E,0x9F,0xA7,0xA7,0x9F,0x4E,0x3C};
/*                                 
char shape_pokeball[8]        = {0b00111100,
                                 0b01111110,
                                 0b11111111,
                                 0b11100111,
                                 0b10100101,
                                 0b10011001,
                                 0b01000010,
                                 0b00111100};*/
                                 
char shape_heart_f[8]         = {0x0C,0x1E,0x3E,0x7C,0x7C,0x3E,0x1E,0x0C};
/*
char shape_heart_f[8]         = {0b00000000,
                                 0b01100110,
                                 0b11111111,
                                 0b11111111,
                                 0b01111110,
                                 0b00111100,
                                 0b00011000,
                                 0b00000000};*/

void LedMat(char vector[], int time, short logic);
void InvMat(char vector[], int time, short logic);
void FixMat(char vector[], int time, short logic, int offset);

void startup(void)
{
   set_tris_a(0);    output_a(0);
   set_tris_b(0);    output_b(0);
   set_tris_c(0);    output_c(0);
   set_tris_d(0);    output_d(0);
   
   //startup
   
   PB7=1;//output_b(0b10000000);
   output_high(C1);
   delay_ms(100);
   
   PB6=1;//output_b(0b11000000);
   output_high(C2);
   output_low(C1);
   delay_ms(100);
   
   PB5=1;//output_b(0b11100000);
   output_high(C3);
   output_low(C2);
   delay_ms(100);
   
   PB4=1;//output_b(0b11110000);
   output_high(C4);
   output_low(C3);
   delay_ms(100);
   
   PB3=1;//output_b(0b11111000);
   output_high(C5);
   output_low(C4);
   delay_ms(100);
   
   PB2=1;//output_b(0b11111100);
   output_high(C6);
   output_low(C5);
   delay_ms(100);
   
   PB1=1;//output_b(0b11111110);
   output_high(C7);
   output_low(C6);
   delay_ms(100);
   
   PB0=1;//output_b(0b11111111);
   output_high(C8);
   output_low(C7);
   delay_ms(100);
   
   output_low(C8);
}

void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   
   startup();
   
    while(true)
    {
      
      while(input(BTN))
      {
         FixMat(shape_pokeball,1,1,0);
      }
      
      while(!input(BTN))
      {
         FixMat(shape_heart_f,1,0,0);
         FixMat(shape_heart_f,1,1,0);
      }
      
      LedMat(message,2,1);
      InvMat(message,2,1);
      
      LedMat(message,2,0);
      InvMat(message,2,0);
    }

}

void LedMat(char vector[], int time, short logic)
{
   int n_letters = 6;
   int length = 17 + (5 * n_letters);        // es necesario que length sea flotante         estas 2 deberan cambiar                               
   int c_lim = length - 8;         // quiza se realiza una clase de conversion
   
   int i;                                 // a flotante por lo que sin float no se muestra
   int j;                                // nada al realizar LM[i + c]
   int k;
   int c;                             
   
   for(c = 0; c < c_lim; c++)
   {
      for(k = 0; k < time; k++)
      {
         for(j = 0; j < 62; j++)
         {
            for(i = 0; i < 8; i++)
            {
               if(logic)
               {
                  output_b(vector[i + c]);
               }
               else
               {
               output_bit(PIN_B0,!bit_test(vector[i + c],0));
               output_bit(PIN_B1,!bit_test(vector[i + c],1));
               output_bit(PIN_B2,!bit_test(vector[i + c],2));
               output_bit(PIN_B3,!bit_test(vector[i + c],3));
               output_bit(PIN_B4,!bit_test(vector[i + c],4));
               output_bit(PIN_B5,!bit_test(vector[i + c],5));
               output_bit(PIN_B6,!bit_test(vector[i + c],6));
               output_bit(PIN_B7,!bit_test(vector[i + c],7));
               }
      
               switch (i) 
               {
                  case 0: 
                     output_bit(C1,1);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 1:
                     output_bit(C1,0);
                     output_bit(C2,1);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 2: 
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,1);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 3:
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,1);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 4: 
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,1);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 5:
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,1);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 6: 
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,1);
                     output_bit(C8,0);
                     break;
                  case 7:
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,1);
                     break;
                  default:
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
               }

               delay_us(100);
      
               output_bit(C1,0);
               output_bit(C2,0);
               output_bit(C3,0);
               output_bit(C4,0);
               output_bit(C5,0);
               output_bit(C6,0);
               output_bit(C7,0);
               output_bit(C8,0);
            }
         }
      }
   }
}

void InvMat(char vector[], int time, short logic)
{
   int n_letters = 6;
   int length = 17 + (5 * n_letters);        // es necesario que length sea flotante         estas 2 deberan cambiar                               
   int c_lim = length - 8;         // quiza se realiza una clase de conversion
   
   int i;                                 // a flotante por lo que sin float no se muestra
   int j;                                // nada al realizar LM[i + c]
   int k;
   int c;                             
   
   for(c = c_lim - 1; c >= 0 && c <= c_lim; c--)
   {
      for(k = 0; k < time; k++)
      {
         for(j = 0; j < 62; j++)
         {
            for(i = 0; i < 8; i++)
            {
               if(logic)
               {
                  output_b(vector[i + c]);
               }
               else
               {
               output_bit(PIN_B0,!bit_test(vector[i + c],0));
               output_bit(PIN_B1,!bit_test(vector[i + c],1));
               output_bit(PIN_B2,!bit_test(vector[i + c],2));
               output_bit(PIN_B3,!bit_test(vector[i + c],3));
               output_bit(PIN_B4,!bit_test(vector[i + c],4));
               output_bit(PIN_B5,!bit_test(vector[i + c],5));
               output_bit(PIN_B6,!bit_test(vector[i + c],6));
               output_bit(PIN_B7,!bit_test(vector[i + c],7));
               }
      
               switch (i) 
               {
                  case 0: 
                     output_bit(C1,1);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 1:
                     output_bit(C1,0);
                     output_bit(C2,1);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 2: 
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,1);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 3:
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,1);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 4: 
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,1);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 5:
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,1);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
                  case 6: 
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,1);
                     output_bit(C8,0);
                     break;
                  case 7:
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,1);
                     break;
                  default:
                     output_bit(C1,0);
                     output_bit(C2,0);
                     output_bit(C3,0);
                     output_bit(C4,0);
                     output_bit(C5,0);
                     output_bit(C6,0);
                     output_bit(C7,0);
                     output_bit(C8,0);
                     break;
               }

               delay_us(100);
      
               output_bit(C1,0);
               output_bit(C2,0);
               output_bit(C3,0);
               output_bit(C4,0);
               output_bit(C5,0);
               output_bit(C6,0);
               output_bit(C7,0);
               output_bit(C8,0);
            }
         }
      }
   }
}

void FixMat(char vector[], int time, short logic, int offset)
{
   int i;                               
   int j;                    
   long c;
   
   for(c = 0; c < time; c++)
   {
      for(j = 0; j < 62; j++)  //125 = 0.1 sec... in real world 62 = 0.1 sec
      {
         for(i = 0; i < 8; i++)
         {
            if(logic)
            {
               output_b(vector[i + offset]);
            }
            else
            {
               output_bit(PIN_B0,!bit_test(vector[i + offset],0));
               output_bit(PIN_B1,!bit_test(vector[i + offset],1));
               output_bit(PIN_B2,!bit_test(vector[i + offset],2));
               output_bit(PIN_B3,!bit_test(vector[i + offset],3));
               output_bit(PIN_B4,!bit_test(vector[i + offset],4));
               output_bit(PIN_B5,!bit_test(vector[i + offset],5));
               output_bit(PIN_B6,!bit_test(vector[i + offset],6));
               output_bit(PIN_B7,!bit_test(vector[i + offset],7));
            }
      
            switch (i) 
            {
               case 0: 
                  output_bit(C1,1);
                  output_bit(C2,0);
                  output_bit(C3,0);
                  output_bit(C4,0);
                  output_bit(C5,0);
                  output_bit(C6,0);
                  output_bit(C7,0);
                  output_bit(C8,0);
                  break;
               case 1:
                  output_bit(C1,0);
                  output_bit(C2,1);
                  output_bit(C3,0);
                  output_bit(C4,0);
                  output_bit(C5,0);
                  output_bit(C6,0);
                  output_bit(C7,0);
                  output_bit(C8,0);
                  break;
               case 2: 
                  output_bit(C1,0);
                  output_bit(C2,0);
                  output_bit(C3,1);
                  output_bit(C4,0);
                  output_bit(C5,0);
                  output_bit(C6,0);
                  output_bit(C7,0);
                  output_bit(C8,0);
                  break;
               case 3:
                  output_bit(C1,0);
                  output_bit(C2,0);
                  output_bit(C3,0);
                  output_bit(C4,1);
                  output_bit(C5,0);
                  output_bit(C6,0);
                  output_bit(C7,0);
                  output_bit(C8,0);
                  break;
               case 4: 
                  output_bit(C1,0);
                  output_bit(C2,0);
                  output_bit(C3,0);
                  output_bit(C4,0);
                  output_bit(C5,1);
                  output_bit(C6,0);
                  output_bit(C7,0);
                  output_bit(C8,0);
                  break;
               case 5:
                  output_bit(C1,0);
                  output_bit(C2,0);
                  output_bit(C3,0);
                  output_bit(C4,0);
                  output_bit(C5,0);
                  output_bit(C6,1);
                  output_bit(C7,0);
                  output_bit(C8,0);
                  break;
               case 6: 
                  output_bit(C1,0);
                  output_bit(C2,0);
                  output_bit(C3,0);
                  output_bit(C4,0);
                  output_bit(C5,0);
                  output_bit(C6,0);
                  output_bit(C7,1);
                  output_bit(C8,0);
                  break;
               case 7:
                  output_bit(C1,0);
                  output_bit(C2,0);
                  output_bit(C3,0);
                  output_bit(C4,0);
                  output_bit(C5,0);
                  output_bit(C6,0);
                  output_bit(C7,0);
                  output_bit(C8,1);
                  break;
               default:
                  output_bit(C1,0);
                  output_bit(C2,0);
                  output_bit(C3,0);
                  output_bit(C4,0);
                  output_bit(C5,0);
                  output_bit(C6,0);
                  output_bit(C7,0);
                  output_bit(C8,0);
                  break;
            }

            delay_us(100);
      
            output_bit(C1,0);
            output_bit(C2,0);
            output_bit(C3,0);
            output_bit(C4,0);
            output_bit(C5,0);
            output_bit(C6,0);
            output_bit(C7,0);
            output_bit(C8,0);
         }
      }
   }
}

