#include "mouse.h"
#include "onoff.h"

int mouse_signal(int * mousig)
{
	return 0;
}

Mouse_move::Mouse_move(int x, int y)
{
	x0 = x;
	y0 = y;
}

int Mouse_move::update(int x1, int y1)
{
	dx = x1 - x0;
	dy = y1 - y0;
	x0 = x1;
	y0 = y1;
	return 0;
}