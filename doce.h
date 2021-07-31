#ifndef DOCE_H
#define DOCE_H

/*			Led's Console Graphics Library  		*/


typedef enum
{
	NOCOLOR,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	BRIGHT_WHITE,
	GREY,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	BRIGHT_PURPLE,
	BRIGHT_YELLOW,
	WHITE
} Color;


typedef struct
{
	char ch;
	Color fg_color; // foreground
	Color bg_color; // background
} Pixel;


typedef struct
{
	int sizeX, sizeY;
	Pixel *matrix;
} Screen;


void init_screen(Screen *scr, int size_x, int size_y);
void free_screen(Screen *scr);

void draw_screen(Screen *scr);
void clear_screen(Screen *scr);

Pixel* getpixel(Screen *scr, int x, int y);
void putpixel(Screen *scr, Pixel pix, int x, int y); // sets pixel in matrix and draws it on a screen
void clearpixel(Screen *scr, int x, int y);
void setpixel(Screen *scr, Pixel pix, int x, int y); // only sets pixel in matrix without drawing
void drawpixel(Screen *scr, int x, int y); // draws an already existing pixel

void _goto(int x, int y); // moves console cursor


#endif