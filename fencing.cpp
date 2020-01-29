#include <iostream>
#include <string>
#include <ncurses.h>
#include <cmath>
#include "stances.h"
// g++ test.cpp -lncurses
// g++ test.cpp -lncurses -o fencing.out
// g++ fencing.cpp -lncurses -o f.out

using namespace std;
void DrawBoard();
void PlacePlayerOne();
void PlacePlayerZero();
void ResetBoard();
char p0input;
char p1input;
int p0pos = 2;
int p1pos = 6;
int p0stance ;
int p1stance ;
int boardsize = 8;
int squaresize = 10;
int totalrows = 5;
char rows[5][96] ;

char row0[80];
char row1[80];
char row2[80];
char row3[80];
char row4[80];
  WINDOW * win;

void ExecuteInputs()
{
 if(p0input == 1)
 {p0pos = p0pos + 1;}
 if(p0input == 2)
 {p0pos = p0pos - 1;}
 if(p1input == 1)
 {p1pos = p1pos + 1;}
 if(p1input == 2)
 {p1pos = p1pos - 1;}
	//reset player inputs to blank
	p0input = 0;
	p1input = 0;

}
void SetPlayerInputs(int keypressed)
{
   //q 81 w 119 e 101
	 //a 97 s 115 d 100
	 //z 122 x 120 c 99

	 // i 105 o 111 p 112  numlock on  7 55 8 56 9 57
	 // k 107 l 108 ; 59   numlock on  4 52 5 53 6 54
	 // , 44 . 46 / 47			numlock on 	1 49 2 50 3 51
		if( keypressed == 81 || keypressed == 119 || keypressed == 101 )
		{p0input = 3; p0stance = 2;}
			if( keypressed == 97 || keypressed == 115 || keypressed == 100 )
			{p0input = 3;p0stance = 1;}
				if( keypressed == 122 || keypressed == 120 || keypressed == 99 )
				{p0input = 3;p0stance = 0;}



			if( keypressed == 105 || keypressed == 111 || keypressed == 112 )
			{p1input = 1;p1stance = 2;}
				if( keypressed == 107 || keypressed == 108 || keypressed == 59 )
				{p1input = 2;p1stance = 1;}
					if( keypressed == 44 || keypressed == 46 || keypressed == 47 )
					{p1input = 3;p1stance = 0;}


			if(p1input != 0 && p0input != 0)
			{
				ExecuteInputs();
					ResetBoard();
				PlacePlayerZero();
				PlacePlayerOne();
				DrawBoard();

			}



}
void DrawBoard()
{
	int count = 0;
	int rowcount = 0;
	int colcount = 0;

		rowcount = 0;
		while (rowcount < 5)
		{
			colcount = 0;
			while (colcount < squaresize * boardsize)
			{
					wprintw(win,"%c", rows[rowcount][colcount]);
				colcount = colcount + 1;
			}
			rowcount = rowcount + 1;
			wprintw(win,"\n");
		}



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
			while (colcount < 84)
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

	while (rowcount < 5)
	{
		colcount = 0;
		while (colcount < squaresize)
		{
			rows[rowcount][colcount + (p0pos * squaresize)] = p0s0[p0stance][rowcount][colcount];
			colcount = colcount + 1;
		}
			rowcount = rowcount + 1;
	}

}
void PlacePlayerOne()
{
	int rowcount = 0;
	int colcount = -2;
	char c = 0;
	while (rowcount < 5)
	{
		colcount = -2;
		while (colcount <= squaresize - 2)
		{

			 c = rows[rowcount][colcount + (p1pos * squaresize) ];
			if(c == 45 && p1s0[p1stance][rowcount][colcount + 2] == 45)
			{		rows[rowcount][colcount + (p1pos * squaresize) ] = 120;}
				else
				{
					if(p1s0[p1stance][rowcount][colcount + 2] != 32)
					{rows[rowcount][colcount + (p1pos * squaresize) ] = p1s0[p1stance][rowcount][colcount + 2]; }


				}
			// rows[rowcount][colcount + (p1pos * squaresize) - 2] = p1s0[p1stance][rowcount][colcount];
			colcount = colcount + 1;
		}
		rowcount = rowcount + 1;
	}

}
int main()
{
 p0stance = 1;
 p1stance = 0;
	int inputchar;
	int x;
	int d;
  int dir;
int height;
int width;
  dir = 1;
	d = 0;
	x = 1;
	initscr();			/* Start curses mode 		*/
//= newwin(200, 200, 0,0);
  getmaxyx(stdscr, height, width);
   win = newwin(height - 2, width - 2, 1, 1);
	raw();				/* Line buffering disabled	*/
	keypad(win, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
  scrollok(win,TRUE);
    	wprintw(win,"Fight\n");

//x used to check for escape char which is set to [z]
		while( x == 1){
				inputchar= getch();
	if( inputchar== KEY_F(1))
				//ignore Fkeys
					wprintw(win,"F1 Key pressed");

	else
	{
		//48 is 0 122 is lowercase x
		if( inputchar > 30 && inputchar < 123)
		{
			// wprintw(win,"%c", inputchar);
				// wprintw(win,"\n");

				//set input for players
				SetPlayerInputs(inputchar);

			//
      // if(d % 8 == 0)
      // {
			//
      // int count = 0;
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p0s00[count]);
      //   count = count + 1;
      // }
      // count = 0;
      // while ((count + 1) < abs(p0pos - p1pos) )
      // {
      //   wprintw(win,"    ");
      //   count = count + 1;
      // }
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p1s00[count]);
      //   count = count + 1;
      // }
      // wprintw(win,"\n");
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p0s01[count]);
      //   count = count + 1;
      // }
      // count = 0;
      // while ((count + 1) < abs(p0pos - p1pos) )
      // {
      //   wprintw(win,"    ");
      //   count = count + 1;
      // }
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p1s01[count]);
      //   count = count + 1;
      // }
      // wprintw(win,"\n");
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p0s02[count]);
      //   count = count + 1;
      // }
			//
      // count = 0;
      // while ((count + 1) < abs(p0pos - p1pos) )
      // {
      //   wprintw(win,"    ");
      //   count = count + 1;
      // }
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p1s02[count]);
      //   count = count + 1;
      // }
      //   wprintw(win,"\n");
      //   count = 0;
			//
      //   while (count < 11)
      //   {
      //     wprintw(win,"%c", p0s03[count]);
      //       count = count + 1;
      //   }
      //       count = 0;
      //       while ((count + 1) < abs(p0pos - p1pos) )
      //       {
      //         wprintw(win,"    ");
      //         count = count + 1;
      //       }
      //       count = 0;
			//
			//
      //   count = 0;
      //   while (count < 11)
      //   {
      //     wprintw(win,"%c", p1s03[count]);
      //     count = count + 1;
      //   }
      //     wprintw(win,"\n");
			//
			//
      //     count = 0;
			//
      //     while (count < 11)
      //     {
      //       wprintw(win,"%c", p0s04[count]);
      //         count = count + 1;
      //     }
      //         count = 0;
      //         while ((count + 1) < abs(p0pos - p1pos) )
      //         {
      //           wprintw(win,"    ");
      //           count = count + 1;
      //         }
      //         count = 0;
			//
			//
      //     count = 0;
      //     while (count < 11)
      //     {
      //       wprintw(win,"%c", p1s04[count]);
      //       count = count + 1;
      //     }
      //       wprintw(win,"\n");
			//
      // }
      //   else{
			//
			//
      // int count = 0;
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p0s10[count]);
      //   count = count + 1;
      // }
      // count = 0;
      // while ((count + 1) < abs(p0pos - p1pos) )
      // {
      //   wprintw(win,"    ");
      //   count = count + 1;
      // }
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p1s10[count]);
      //   count = count + 1;
      // }
      // wprintw(win,"\n");
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p0s11[count]);
      //   count = count + 1;
      // }
      // count = 0;
      // while ((count + 1) < abs(p0pos - p1pos) )
      // {
      //   wprintw(win,"    ");
      //   count = count + 1;
      // }
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p1s11[count]);
      //   count = count + 1;
      // }
      // wprintw(win,"\n");
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p0s12[count]);
      //   count = count + 1;
      // }
			//
      // count = 0;
      // while ((count + 1) < abs(p0pos - p1pos) )
      // {
      //   wprintw(win,"    ");
      //   count = count + 1;
      // }
      // count = 0;
      // while (count < 11)
      // {
      //   wprintw(win,"%c", p1s12[count]);
      //   count = count + 1;
      // }
      // 	wprintw(win,"\n");
      //   count = 0;
			//
      //   while (count < 11)
      //   {
      //     wprintw(win,"%c", p0s13[count]);
      //       count = count + 1;
      //   }
      //       count = 0;
      //       while ((count + 1) < abs(p0pos - p1pos) )
      //       {
      //         wprintw(win,"    ");
      //         count = count + 1;
      //       }
      //       count = 0;
			//
			//
      //   count = 0;
      //   while (count < 11)
      //   {
      //     wprintw(win,"%c", p1s13[count]);
      //     count = count + 1;
      //   }
      //     wprintw(win,"\n");
			//
			//
      //     count = 0;
			//
      //     while (count < 11)
      //     {
      //       wprintw(win,"%c", p0s14[count]);
      //         count = count + 1;
      //     }
      //         count = 0;
      //         while ((count + 1) < abs(p0pos - p1pos) )
      //         {
      //           wprintw(win,"    ");
      //           count = count + 1;
      //         }
      //         count = 0;
			//
			//
      //     count = 0;
      //     while (count < 11)
      //     {
      //       wprintw(win,"%c", p1s14[count]);
      //       count = count + 1;
      //     }
      //       wprintw(win,"\n");
      //     }
			//
			// wprintw(win,"\n");
			//
      // p1pos = p1pos + (1 * dir);
      // if(p1pos > 8){dir = -1;}
      // if(p1pos <= 0){dir = 1;p1pos = 1;}
      // d = d + (4 * dir);
      // if(d > 16){dir = -1;}
      // if(d <= 0){dir = 1;d = 0;}



	 }
		if( inputchar== 122){x = 2;}
	}
	wrefresh(win);

}
endwin();
	return 0;
}
