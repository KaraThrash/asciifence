#include <iostream>
#include <string>
#include <ncurses.h>
#include <cmath>
#include "fencing.h"
#include "stances.h"
// g++ test.cpp -lncurses
// g++ test.cpp -lncurses -o fencing.out
// g++ fencing.cpp -lncurses -o f.out

using namespace std;

//TODO: error message if terminal is to small

//TODO: break into utils file
int sign(int x)
{
      if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
int string_size(const char * str)
{
    // const char * str = "Hello World !";
    int size = 0;
    while (str[size] != '\0') size++;
    return size;
}
void GripChange(int p0change,int p1change)
{
  if(p0change == grip || p0change == -grip )
  {
    p0stance = p0stance + p0change;
    p0result = "===p0 grip change";
    //high med low grip
    if(p0stance < 0){p0stance = 0;}
      if(p0stance > 2){p0stance = 2;}
  }
  if(p1change == 1 || p1change == -1 )
  {
      //high med low grip
        p1result = "===p1 grip change";
    p1stance = p1stance + p1change;
    if(p1stance < 0){p1stance = 0;}
      if(p1stance > 2){p1stance = 2;}
  }
}
void ThrustAttack(int p0change,int p1change)
{
  if(p0change == thrust && p1change == thrust) // both thrust
  {
    if(p0stance != p1stance){
            p0result = "===p0 thrust, and hit";
            p1result = "===p1 thrust, and hit";
        } //both hit
    else{p0result = "===p0 thrust, and miss";
    p1result = "===p1 thrust, and miss";} //bounce off

  }
  else
  {
    if(p0change == thrust ) // player 0 thrust
    {
      if(abs(p1change) == parry && p1stance == p0stance){p0result = "===p0 thrust, and p1 parries";} //parry beats thrust at same grip
        if(abs(p1change) == grip && p1stance == p0stance){p0result = "===p0 thrust, and p1 deflects";} //grip change blocks thrust at same grip
        else{p0result = "===p0 thrust, and hits";} //p0 hits

    }
    if(p1change == thrust ) // player 1 thrust
    {
      if(abs(p0change) == parry && p1stance == p0stance){p1result = "===p1 thrust, and p0 parries";} //parry beats thrust at same grip
        if(abs(p0change) == grip && p1stance == p0stance){p1result = "===p1 thrust, and p0 deflects";} //grip change blocks thrust at same grip
        else{} //p0 hits

    }
  }

}
void SlashAttack(int p0change,int p1change)
{
  if(p0change == slash && p1change == slash) // both slash
  {
    p0result = "===p0 slash, and misses";
      p1result = "===p1 slash, and misses";
    //bounce off
  }
  else
  {
    if(p0change == slash ) // player 0 thrust
    {
      if(abs(p1change) == block && abs(p1stance - p0stance) <= 1){p0result = "===p0 slash, and p1 blocks";} //block protects 2 spaces //there is no mid block
        else{p0result = "===p0 slash, and hit";} //p0 hits

    }
    if(p1change == slash ) // player 1 thrust
    {
      if(abs(p0change) == block && abs(p1stance - p0stance) <= 1){p1result = "===p1 slash, and p0 blocks";} //block protects 2 spaces //there is no mid block
        else{p1result = "===p1 slash, and hit";} //p0 hits

    }
  }

}


//TODO: clean this up: the logic can be more concise for checking turns where both players move
void PlayerMove(int p0change,int p1change)
{



    //if player is at the edge they cant move in that direction
    if( p1pos >= boardsize - 1 && p1change == movement){p1change = 0; p1result = "===p1's back is against the wall";}
    if( p0pos <= 0 && p0change == -movement){p0change = 0;p0result = "===p0's back is against the wall";}


      //both players move
    if(abs(p0change) == movement && abs(p1change) == movement)
    {
            if((sign(p0change) + p0pos) == (sign(p1change) + p1pos ) || (sign(p0change) + p0pos) >= (sign(p1change) + p1pos)  || (sign(p1change) + p1pos) <= (sign(p0change) + p0pos))
            {
              p0result = "===p0 bumps heads";
                p1result = "===p1 bumps heads";
                if( abs(p0pos - p1pos) == 2){ p0pos = p0pos + 1;}
            }else
            {

              p0pos = (sign(p0change) + p0pos) ;
                p1pos = (sign(p1change) + p1pos) ;
              p0result = "===p0 moves";
                p1result = "===p1 moves";

            }

    }else
    {

      if(abs(p0change) == movement )
      {
              if((sign(p0change) + p0pos) != p1pos && (sign(p0change) + p0pos) < p1pos  && (sign(p0change) + p0pos) >= 0  )
              {
                p0pos = (sign(p0change) + p0pos) ;

              }else{p0result = "===p 0 cant move  :";}

      }
      if(abs(p1change) == movement )
      {
              if((sign(p1change) + p1pos) != p0pos && (sign(p0change) + p1pos) >= p0pos && (sign(p0change) + p1pos) < boardsize)
              {
                p1pos = (sign(p1change) + p1pos) ;
                p1result = "===moves";
              }else{p1result = "===p1 cant move  :";}

      }
    }




}

void ExecuteInputs(int p0action,int p1action)
{
  GripChange(p0action,p1action);
  //can only hit each other when adjacent
  if(abs(p0pos - p1pos) == 1)
  {
    ThrustAttack(p0action,p1action);
    if(roundOn == TRUE )
    {SlashAttack(p0action,p1action);}
  }else
  {
    if(p0cmd == thrust || p0cmd == slash){p0result = "===  p0 out of range  :";}
    if(p1cmd == thrust || p1cmd == slash){p1result = "===  p1 out of range  :";}
  }
  //can only hit each other when adjacent

  if(roundOn == TRUE && (abs(p0action) == movement || abs(p1action) == movement))
  {PlayerMove(p0action,p1action);}

roundOn = FALSE;

	//reset player inputs to blank
	// p0cmd = 0;
	// p1cmd = 0;


}


void SetPlayerInputs(int keypressed)
{
   //q 81 w 119 e 101
	 //a 97 s 115 d 100
	 //z 122 x 120 c 99

	 // i 105 o 111 p 112  numlock on  7 55 8 56 9 57
	 // k 107 l 108 ; 59   numlock on  4 52 5 53 6 54
	 // , 44 . 46 / 47			numlock on 	1 49 2 50 3 51

   //player cmd numbers
   //grip change >> thrust >> slash >> block >> parry >>  move
   //   0 >> 1 >>   2  >>   3   >>    4 u/d   >>  5  >> 6
   if( keypressed == 81  ) //q
   {p0cmd = block; } //block up
   if( keypressed == 119  ) //w
{p0cmd = grip; } //grip up
   if( keypressed == 101 ) //e
   {p0cmd = thrust; } //thrust

   if( keypressed == 97  ) //a
   {p0cmd = -movement; } //move back
   if( keypressed == 115  ) //s
      {p0cmd = parry; } //parry
   if( keypressed == 100 ) //d
   {p0cmd = movement;} //move fwd

   if( keypressed == 122  ) //z
   {p0cmd = -block; } //block down
   if( keypressed == 120  ) //x
  {p0cmd = -grip; } //grip down
   if( keypressed == 99 ) //c
   {p0cmd = slash; } //slash



   if( keypressed == 105  )//i
   {p1cmd = thrust; } //thrust
   if( keypressed == 111  ) // o
   {p1cmd = grip; } //grip up
   if( keypressed == 112 ) //p
   {p1cmd = block; } //block up

   if( keypressed == 107  ) //k
      {p1cmd = -movement;} //move fwd
   if( keypressed == 108  ) //l
     {p1cmd = parry; } //parry
   if( keypressed == 59 ) // ;
      {p1cmd = movement; } //move back

   if( keypressed == 44  ) // ,
     {p1cmd = slash; } //slash
   if( keypressed == 46  ) //.
  {p1cmd = -grip; } //grip down
   if( keypressed == 47 ) ///
     {p1cmd = -block; } //block down



			if(p1cmd != 0 && p0cmd != 0)
			{
        roundOn = TRUE;
				ExecuteInputs(p0cmd,p1cmd);


				ResetBoard();
				PlacePlayerZero();
				PlacePlayerOne();

				DrawBoard();

        //
        p0cmd = 0;
        p1cmd = 0;
			}



}
void DrawBoard()
{
	int count = 0;
	int rowcount = 0;
	int colcount = 0;

      //newlines to move the previous turn further out of the way
    for (int n = 0; n < 10; n++){wprintw(win,"\n");}
    // asterisk for the ceiling and floor to create a hallway visual
    for (int n = 0; n < boardsize * squaresize; n++){wprintw(win,"*");}
    wprintw(win,"\n");
    int p0resultsize = string_size(p0result);
    int p1resultsize = string_size(p1result);
    wprintw(win,"%s",p0result);
    for (int n = 0; n < ( boardsize * squaresize) - (p1resultsize + p0resultsize); n++){wprintw(win," ");}
    wprintw(win,"%s",p1result);
    wprintw(win,"\n");


		rowcount = 0;
		while (rowcount < 5)
		{
        // wprintw(win,"%s", rows[rowcount]);
			colcount = 0;
			while (colcount < (squaresize * boardsize) + 1)
			{
				wprintw(win,"%c", rows[rowcount][colcount]);
				colcount = colcount + 1;
			}
			rowcount = rowcount + 1;
			wprintw(win,"\n");
		}
    // asterisk for the ceiling and floor to create a hallway visual
    wprintw(win,"\n");



    for (int n = 0; n < ( boardsize * squaresize) ; n++){
      if(n % squaresize == 0)
      {
          wprintw(win,"|");
        n = n + 1;
       }
      wprintw(win," ");
      if(n % squaresize == (squaresize / 2))
      {
          wprintw(win,"%c", 49 + (n / squaresize));
        n = n + 1;
       }
    }
    wprintw(win,"\n");
    for (int n = 0; n < boardsize * squaresize; n++){wprintw(win,"*");}


}
void ResetBoard()
{
	int count = 0;
	int rowcount = 0;
	int colcount = 0;

		rowcount = 0;
		while (rowcount < 5)
		{
			colcount = 0;
      //Note: needs to include the last row so that player one animations dont persist
			while (colcount <= (boardsize * squaresize))
			{
				rows[rowcount][colcount ] = 32;
				colcount = colcount + 1;
			}
			rowcount = rowcount + 1;
		}


}

void PlacePlayerZero()
{
	int rowcount = 0;
	int colcount = 0;
  int absp0cmd = abs(p0cmd);
  if(p0cmd == -block){absp0cmd = 6;}
	while (rowcount < 5)
	{
		colcount = 0;
		while (colcount < squaresize )
		{

      if(absp0cmd >= thrust && absp0cmd < movement)
      {

        rows[rowcount][colcount + (p0pos * squaresize)] = p0s0[absp0cmd][rowcount][colcount];

      }
      else
      {rows[rowcount][colcount + (p0pos * squaresize)] = p0s0[p0stance][rowcount][colcount];}

			colcount = colcount + 1;
		}
			rowcount = rowcount + 1;
	}

}
void PlacePlayerOne()
{
	int rowcount = 0;
	int colcount = 0;
    int absp1cmd = abs(p1cmd);
    if(p1cmd == -block){absp1cmd = 6;}
	char c = 0;
	while (rowcount < 5)
	{
		colcount = 0;
		while (colcount <= squaresize )
		{
      if(absp1cmd >= thrust && absp1cmd < movement)
      {

        rows[rowcount][colcount + (p1pos * squaresize)] = p1s0[absp1cmd][rowcount][colcount];

      }
      else
      {rows[rowcount][colcount + (p1pos * squaresize)] = p1s0[p1stance][rowcount][colcount];}

      // rows[rowcount][colcount + (p1pos * squaresize) ] = p1s0[p1stance][rowcount][colcount ];
			//  c = rows[rowcount][colcount + (p1pos * squaresize) ];
			// if(c == 45 && p1s0[p1stance][rowcount][colcount + 2] == 45)
			// {		rows[rowcount][colcount + (p1pos * squaresize) ] = 120;}
			// 	else
			// 	{
      //     rows[rowcount][colcount + (p1pos * squaresize) ] = p1s0[p1stance][rowcount][colcount + 2];
			// 		if(p1s0[p1stance][rowcount][colcount + 2] != 32)
			// 		{ }


				// }
			// rows[rowcount][colcount + (p1pos * squaresize) - 2] = p1s0[p1stance][rowcount][colcount];
			colcount = colcount + 1;
		}
		rowcount = rowcount + 1;
	}

}

void GameLoop()
{
  int inputchar;
  int d;
  int dir;
  dir = 1;
  d = 0;
    inputchar= getch();
    if( inputchar== KEY_F(1))
              //ignore Fkeys
                wprintw(win,"F1 Key pressed");

        else
        {
          //30 is , 122 is lowercase x
          if( inputchar > 30 && inputchar < 123)
          {

              //set input for players
              SetPlayerInputs(inputchar);




         }
         //escape: to exit
          if( inputchar== 27){gameOn = FALSE;}
    }
    wrefresh(win);
}

int main()
{
 p0stance = 1;
 p1stance = 0;

int height;
int width;

	initscr();			/* Start curses mode 		*/
  getmaxyx(stdscr, height, width);
   win = newwin(height / 2, width, 1, 1);
	raw();				/* Line buffering disabled	*/
	keypad(win, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
  scrollok(win,TRUE);
    	wprintw(win,"Fight\n");

//x used to check for escape char which is set to [z]
		while( gameOn){
      GameLoop();
}
endwin();
	return 0;
}
