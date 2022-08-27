#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#byte pcon    = 0x8E 
#use delay(int=4000000)

#use rs232(baud=9600,parity=N,xmit=PIN_B1,rcv=PIN_B0,bits=8)

#define RTC_SCLK PIN_B4
#define RTC_IO   PIN_B5
#define RTC_RST  PIN_B6
#include <DS1302.C>
//VCC1 = Backup battery

#define LED PIN_B3
#define BTN PIN_A1

void main()
{
   bit_set(pcon,3);   //INTOSC = 4Mhz
   
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   set_tris_a(0);
   output_a(0);
   set_tris_b(0);
   output_b(0);
   
   rtc_init();

   int day;
   int mth;
   int year;
   int dow;      //no se que es esto
   int hr;
   int min;
   int sec;
   
   char command = 'y';
   
   int sec_old;
   
   while(TRUE)
   {
      delay_ms(100);
      output_toggle(LED);
      
      rtc_get_date(day,mth,year,dow);
      rtc_get_time(hr,min,sec);
      
      if(sec != sec_old)
      {
         putc(10);
         putc(13);
         printf("     %u:%u:%u      ",hr,min,sec);
         printf("   %u/%u/20%u/%u    ",day,mth,year,dow);
         
         sec_old = sec;
      }
      
      if(input(BTN))
      {
         while(input(BTN))
         command = 84;
      }
      
      if(kbhit())
      {
         command = getc();
      }
      
      if(command == 84 || command == 116)
      {
         do
         {
            printf("\nPlease set the day: ");
            day = getch();
         }while(day < 1 || day > 31);
         
         do
         {
            printf("\nPlease set the month: ");
            mth = getch();
         }while(mth < 1 || mth > 12);
         
         printf("\nPlease set the year: ");
         year = getch();
         
         do
         {
            printf("\nPlease set the hour: ");
            hr = getch();
         }while(hr > 23);
         
         do
         {
            printf("\nPlease set the minutes: ");
            min = getch();
         }while(min > 59);
         
         do
         {
            printf("\nPlease set the seconds: ");
            sec = getch();
         }while(sec > 59);
         
         printf("\nDo you want to update RTC? (Y/N): ");
         command = getch();
         
         if(command == 89 || command == 121)
         {
            rtc_set_datetime(day,mth,year,dow,hr,min,sec);
         }
      }
   }
}
