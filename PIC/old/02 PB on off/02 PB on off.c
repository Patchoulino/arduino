//****** PROGRAMA REALIZADO POR JORGE IVÁN RODRÍGUEZ GALICIA
//****** CORREO jorgeirg@yahoo.com.mx, jorgeirg@hotmail.com
//****** TEL: 449 114 9343, 449 173 9348
//****** FECHA DE MODIFICACIÓN: 1 DE ENERO DE 2015
//****** VERSION DE PROGRAMA: 1
//****** DESCRIPCION:   PROGRAMA DE PRUEBA PARA ENDENDER UN LED POR MEDIO DE UN BOTON
//******                Y APAGAR EL MISMO LED POR MEDIO DE OTRO BOTON
//****** PROGRAMA REALIZADO: UNIVERSIDAD TECNOLOGICA DE AGUASCALIENTES



#include <18F4550.h>
#device adc=8
#include <18Fconfig1.h>




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


   set_tris_c(0x0);                   //configura la puerto c como salidas

   // TODO: USER CODE!!
   int i;
   
   
   for (i=1;i<5;i++)
   {
      output_c(0);
      delay_ms(500);
      output_c(255);
      delay_ms(500);
   }   

  output_c(0);



   while(true)
   {
      if (input(PIN_B3)==1)
         output_bit(PIN_C0,1);
      if (input(PIN_B2)==1)
         output_bit(PIN_C0,0);
      
      
   }
   
}

