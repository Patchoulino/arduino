//////////////////////////////////////////////////////////////////////////
////                              HC-SR04.C                           ////
////                   Driver for Ultrasonic Sensor                   ////
////                                                                  ////
////  void HC-SR04_get_timedistance(int16 time, float distance)       ////
////  	                  					      ////
////  distance is in cm                                               ////
////  	                  					      ////
//////////////////////////////////////////////////////////////////////////

#ifndef HC-SR04_TRG

#define HC-SR04_TRG   PIN_B0
#define HC-SR04_ECH   PIN_B1

#endif

// int16 time;
// float distance;

//setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);

void HC-SR04_get_timedistance(int16 time, float distance)
{
   output_bit(HC-SR04_TRG,1);
   delay_us(10);
   output_bit(HC-SR04_TRG,0);

   while(input(!HC-SR04_ECH))
   set_timer1(0);
   while(input(HC-SR04_ECH))

   time = get_timer1();
   distance = time * 0.028 + 1;
}
