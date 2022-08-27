#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOMCLR                   //Master Clear pin disabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#use delay(int=4000000)

// KEYPAD PINS F = Outputs
#define F1 PIN_A0
#define F2 PIN_A1
#define F3 PIN_A2
#define C1 PIN_A3    //A3,4,5 can only be used as inputs
#define C2 PIN_A4
#define C3 PIN_A5

#define BTN PIN_A7

// BI-COLOR LED MATRIX
#define R1 PIN_B6
#define R2 PIN_B7
#define R3 PIN_A6
#define G1 PIN_B3
#define G2 PIN_B4
#define G3 PIN_B5
#define T1 PIN_B2
#define T2 PIN_B1
#define T3 PIN_B0

int game[3][3] = {(0,0,0)
                  (0,0,0)
                  (0,0,0)};
                    
int score[3][3] = {(0,0,0)
                   (0,0,0)
                   (0,0,0)};
        
int current_matrix = 3;
int player1_wins = 0;
int player2_wins = 0;
int winner = 0;
const int delay_time = 33; //used x3 times in pause to draw led matrix, 33*3 = 99us = .099ms
const int delay_count = 1; //number of times that pause is repeated
                   
void pause(long time, int matrix_selector);
int getn(void);
void fill_matrix(int number);
void scoreboard(void);
void blink_matrix(int matrix_selector);

void main()
{

   set_tris_a(0b10111000);
   set_tris_b(0b00000000);

   setup_oscillator(OSC_4MHZ);

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   
   output_a(0x00);
   output_b(0x00);
   
   int current_player = 1;
   int key;
   
   int i;
   int j;
   
    while((player1_wins + player2_wins) < 9)
    { 
      //fill_matrix(0);
      winner = 0;
    
      while(winner == 0)            //Se corre el juego mientras no haya ganador
      {
         do                         //hasta que se presione una tecla...
         {
            key = getn();
         }while(key == 10);
         while(key == getn()) {};   //if key is still being pressed wait for it to stop
         
         switch(key)
         {
            case 0:
               if(player1_wins == player2_wins == 0)  //Si es el inicio del juego podemos seleccionar quien va primero
               {
                  if(current_player == 1)
                  {
                     current_player = 2;
                     current_matrix = 2;
                  }
                  else
                  {
                     current_player = 1;
                     current_matrix = 1;
                  }
               }
               else
               {
                  current_matrix = 4;
               }
            break;
            
            case 1-9:
               current_matrix = 3;
               
               i = (key - 1) / 3;         //la tecla se transforma en coordenadas para la matriz
         
               if(key >= 1 && key <= 3)   j = key - 1;
               if(key >= 4 && key <= 6)   j = key - 4;
               if(key >= 7 && key <= 9)   j = key - 7;
         
               if(game[i][j] == 0)      //si la casilla seleccionada esta desocupada se procede
               {                          //por marcarla con el jugador actual y se comprueba que no haya ganado ya
                  game[i][j] = current_player;
            
                  if((game[0][0] == game[0][1] == game[0][2]) && game[0][0] != 0)   winner = current_player;
                  if((game[1][0] == game[1][1] == game[1][2]) && game[1][1] != 0)   winner = current_player;
                  if((game[2][0] == game[2][1] == game[2][2]) && game[2][2] != 0)   winner = current_player;
            
                  if((game[0][0] == game[1][0] == game[2][0]) && game[0][0] != 0)   winner = current_player;
                  if((game[0][1] == game[1][1] == game[2][1]) && game[1][1] != 0)   winner = current_player;
                  if((game[0][2] == game[1][2] == game[2][2]) && game[2][2] != 0)   winner = current_player;
            
                  if((game[0][0] == game[1][1] == game[2][2]) && game[1][1] != 0)   winner = current_player;
                  if((game[2][0] == game[1][1] == game[0][2]) && game[1][1] != 0)   winner = current_player;
            
                  current_player++;       //se hace el cambio de jugador
                  if(current_player == 3) current_player = 1;
               }
            break;
         }
      }
      
      do{                           //el juego anterior se muestra hasta que se presiona una tecla
         key = getn();
         blink_matrix(3);
      }while(key == 10);  
      while(key == getn()) 
      {
         blink_matrix(3);
      }   //if key is still being pressed wait for it to stop
         
      //quien haya ganado se lleva sus victorias a su record, esto se usa para ver si es el inicio del juego o no
      if(winner == 1)   player1_wins++;
      if(winner == 2)   player2_wins++;
      
      scoreboard();  // se modifica la matriz de resultados
      current_matrix = 4;
      
      do{
         key = getn();
         blink_matrix(4);
      }while(key == 10);
      while(key == getn()) 
      {
         blink_matrix(4);
      }
    }
    
    if(player1_wins > player2_wins) //Endless loop showing the winner's color and scoreboard
    {
      while(1)
      {
         pause(delay_count,1);
         pause(delay_count,4);
      }
    }
    else if(player1_wins == player2_wins)
    {
      while(1)
      {
         pause(delay_count,0);
         pause(delay_count,4);
      }
    }
    else
    {
      while(1)
      {
         pause(delay_count,2);
         pause(delay_count,4);
      }
    }
}

void pause(long time, int matrix_selector) // default delay that also prints 3x3 led matrix
{
   int t, i, j, player;
   
   for(t=0; t<time; t++)
   {
      for(i=0; i<3; i++)
      {
         for(j=0; j<3; j++)
         {
            switch(matrix_selector)
            {
               case 0:
                  player = 0;
                  break;
               case 1:
                  player = 1;
                  break;
               case 2:
                  player = 2;
                  break;
               case 3:
                  player = game[i][j];
                  break;
               case 4:
                  player = score[i][j];
                  break;
            }
            
            switch(j)
            {
               case 0:
                  if(player == 1)   output_bit(R1,1);
                  if(player == 2)   output_bit(G1,1);
                  break;
               case 1:
                  if(player == 1)   output_bit(R2,1);
                  if(player == 2)   output_bit(G2,1);
                  break;
               case 2:
                  if(player == 1)   output_bit(R3,1);
                  if(player == 2)   output_bit(G3,1);
                  break;
            }
         }
         
         if(i == 0)  output_bit(T1,1);
         if(i == 1)  output_bit(T2,1);
         if(i == 2)  output_bit(T3,1);
         
         delay_us(delay_time);
         
         output_bit(R1,0);
         output_bit(R2,0);
         output_bit(R3,0);
         output_bit(G1,0);
         output_bit(G2,0);
         output_bit(G3,0);
         output_bit(T1,0);
         output_bit(T2,0);
         output_bit(T3,0);
      }
   }
}

int getn(void) // 3x3 keyboard function returns 10 if nothing pressed
{
   int n = 10;
   
   output_bit(F1,1);
   if(input(C1))  n = 1;
   if(input(C2))  n = 2;
   if(input(C3))  n = 3;
   pause(delay_count,current_matrix);
  
   output_bit(F1,0);
   output_bit(F2,1);
   if(input(C1))  n = 4;
   if(input(C2))  n = 5;
   if(input(C3))  n = 6;
   pause(delay_count,current_matrix);
   
   output_bit(F2,0);
   output_bit(F3,1);
   if(input(C1))  n = 7;
   if(input(C2))  n = 8;
   if(input(C3))  n = 9;
   pause(delay_count,current_matrix);
   
   output_bit(F3,0);
   if(input(BTN)) n = 0;
   
   return n;
}

void fill_matrix(int number) // cleans the game matrix by setting all zeros
{
   int i, j;

   for(i=0; i<3; i++)            //Se limpia la matriz para 
   {                             //juego nuevo
      for(j=0; j<3; j++)
      {
         game[i][j] = number;
      }
   }
}

void scoreboard(void) // draws the scoreboard into the matrix variable
{
   int i, j;
   short scored = 0;

   for(i=0; i<3; i++)             
   {                             
      for(j=0; j<3; j++)
      {
         if(score[i][j] == 0 && scored == 0)
         {
            score[i][j] = winner;
            scored = 1;
         }
      }
   }
}

void blink_matrix(int matrix_selector)
{
   switch(current_matrix)
   {
      case 0:
         switch(matrix_selector)
         {
            case 3:
               current_matrix = 3;
               break;
            case 4:
               current_matrix = 4;
               break;
         }
         break;
      case 3:
         current_matrix = 0;
         break;
      case 4:
         current_matrix = 0;
         break;
   }
}
