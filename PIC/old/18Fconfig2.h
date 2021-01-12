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
#FUSES IESO                  	//Internal External Switch Over mode enabled
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
#FUSES ICPRT                 	//ICPRT enabled
