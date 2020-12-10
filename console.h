#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

//////////////
// INCLUDES //
//////////////
#include <Windows.h>
#include <conio.h>

///////////////////
// COLORS VALUES //
///////////////////
#define BLACK       0
#define DARK_BLUE   1
#define GREEN       2
#define WATER_GREEN 3
#define BORDEAUX    4
#define PURPLE      5
#define OLIVE_GREEN 6
#define LIGHT_GREY  7
#define GREY        8
#define BLUE        9
#define LIMON_GREEN 10
#define LIGHT_BLUE  11
#define RED         12
#define FUCSIA      13
#define YELLOW      14
#define WHITE       15

//////////
// KEYS //
//////////
#define KEY_ENTER 13
#define KEY_UP    72
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define KEY_LEFT  75

// console window handle //
static HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

///////////////
// FUNCTIONS //
///////////////
COORD getpos();
void moveto(short x, short y);
void setcolor(int fg, int bg = BLACK);
void setcursor(bool visible);
#define RESETCOLOR setcolor(WHITE, BLACK)

#endif // CONSOLE_H_INCLUDED