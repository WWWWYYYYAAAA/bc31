#include <graphics.h>
#include "windows.h"

Windows::Windows(int ix1, int iy1, int ix2, int iy2, int icolor1, int icolor2)
{
	x1 = ix1;
	y1 = iy1;
	x2 = ix2;
	y2 = iy2;
	color1 = icolor1;
	color2 = icolor2;
	setfillstyle(SOLID_FILL, color1);
	bar(x1+20, y1+20, x2+20, y2+20);
	setfillstyle(SOLID_FILL, color2);
	bar(x1, y1, x2, y2);
}