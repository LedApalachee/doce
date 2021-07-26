#include "doce.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

Pixel* getpixel(Screen *scr, int x, int y)
{
	if (x < 0 && x >= scr->sizeX && y < 0 && y >= scr->sizeY) return 0;
	return &scr->matrix[x * scr->sizeY + y];
}


void init_screen(Screen *scr, int sx, int sy)
{
	scr->sizeX = sx;
	scr->sizeY = sy;
	scr->matrix = (Pixel*) malloc(sizeof(Pixel) * sx * sy);

	for (int x = 0; x < sx; ++x)
		for (int y = 0; y < sy; ++y)
			*getpixel(scr, x,y) = (Pixel){'\0', NOCOLOR};
}


void free_screen(Screen *scr)
{
	free(scr->matrix);
}


inline void _goto(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x,y});
}


void draw_screen(Screen *scr)
{
	CONSOLE_SCREEN_BUFFER_INFO origin;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &origin);
	for (int x = 0; x < scr->sizeX; ++x)
		for (int y = 0; y < scr->sizeY; ++y)
		{
			_goto(x,y);
			SetConsoleTextAttribute(console, (getpixel(scr, x,y)->bg_color * 16 + getpixel(scr, x,y)->fg_color));
			putchar(getpixel(scr, x,y)->ch);
		}
	SetConsoleCursorPosition(console, origin.dwCursorPosition);
	SetConsoleTextAttribute(console, origin.wAttributes);
}


void clear_screen(Screen *scr)
{
	CONSOLE_SCREEN_BUFFER_INFO origin;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &origin);
	for (int x = 0; x < scr->sizeX; ++x)
		for (int y = 0; y < scr->sizeY; ++y)
		{
			_goto(x,y);
			SetConsoleTextAttribute(console, NOCOLOR);
			putchar(' ');
			*getpixel(scr, x,y) = (Pixel){'\0', NOCOLOR, NOCOLOR};
		}
	SetConsoleCursorPosition(console, origin.dwCursorPosition);
	SetConsoleTextAttribute(console, origin.wAttributes);
}


void putpixel(Screen *scr, Pixel pix, int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO origin;
	GetConsoleScreenBufferInfo(console, &origin);

	if (getpixel(scr, x,y))
	{
		*getpixel(scr, x,y) = pix;
		SetConsoleTextAttribute(console, (getpixel(scr, x,y)->bg_color * 16 + getpixel(scr, x,y)->fg_color));
		_goto(x,y);
		putchar(getpixel(scr, x,y)->ch);
	}

	SetConsoleCursorPosition(console, origin.dwCursorPosition);
	SetConsoleTextAttribute(console, origin.wAttributes);
}


void clearpixel(Screen *scr, int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO origin;
	GetConsoleScreenBufferInfo(console, &origin);

	if (getpixel(scr, x,y))
	{
		*getpixel(scr, x,y) = (Pixel){'\0', NOCOLOR, NOCOLOR};
		SetConsoleTextAttribute(console, NOCOLOR);
		_goto(x,y);
		putchar(' ');
	}

	SetConsoleCursorPosition(console, origin.dwCursorPosition);
	SetConsoleTextAttribute(console, origin.wAttributes);
}


void setpixel(Screen *scr, Pixel pix, int x, int y)
{
	if (getpixel(scr, x,y)) *getpixel(scr, x,y) = pix;
}


void drawpixel(Screen *scr, int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO origin;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &origin);

	_goto(x,y);
	SetConsoleTextAttribute(console, (getpixel(scr, x,y)->bg_color * 16 + getpixel(scr, x,y)->fg_color));
	putchar(getpixel(scr, x,y)->ch);

	SetConsoleCursorPosition(console, origin.dwCursorPosition);
	SetConsoleTextAttribute(console, origin.wAttributes);
}