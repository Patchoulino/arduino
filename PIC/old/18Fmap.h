   #byte pie1     = 0xf9d    

   #byte t3con    = 0xfb1    
   #byte ccp2con  = 0xfba
   #byte ccpr2l   = 0xfbb
   #byte ccp1con  = 0xfbd
   #byte ccpr1l   = 0xfbe
   #byte adcon2   = 0xfc0
   #byte adcon1   = 0xfc1
   #byte adcon0   = 0xfc2
   #byte adresl   = 0xfc3
   #byte adresh   = 0xfc4

   #byte t2con    = 0xfca 
   #byte pr2  	  = 0xfcb
   #byte t1con    = 0xfcd 
   #byte t0con    = 0xfd5
   #byte intcon   = 0xff2
   #byte intcon2  = 0xff1
   


   #word ccpr1    = 0xfbe
   #word adc      = 0xfc3
   #word tmr1     = 0xfce
   #word tmr0     = 0xfd6

//Covertidor AD
#bit adon	= adcon0.0
#bit go		= adcon0.1
