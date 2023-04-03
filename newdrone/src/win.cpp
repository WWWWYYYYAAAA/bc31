#include <graphics.h>
#include <alloc.h>
#include "win.h"

Win::Win(int ix1, int iy1, int ix2, int iy2, int icolor1, int icolor2)
{
	x1 = ix1;
	y1 = iy1;
	x2 = ix2;
	y2 = iy2;
	imsize = imagesize(x1, y1, x2+20, y2+20);
	imagebuff = (void far *) farmalloc(imsize);
	getimage(x1, y1, x2+20, y2+20, imagebuff);
	color1 = icolor1;
	color2 = icolor2;
	setfillstyle(SOLID_FILL, color1);
	bar(x1+20, y1+20, x2+20, y2+20);
	setfillstyle(SOLID_FILL, color2);
	bar(x1, y1, x2, y2);
}

int Win::update(int ix1, int iy1, int ix2, int iy2, int icolor1, int icolor2)
{
	putimage(x1, y1, imagebuff, COPY_PUT);
	x1 = ix1;
	y1 = iy1;
	x2 = ix2;
	y2 = iy2;
	color1 = icolor1;
	color2 = icolor2;
	getimage(x1, y1, x2+20, y2+20, imagebuff);
	setfillstyle(SOLID_FILL, color1);
	bar(x1+20, y1+20, x2+20, y2+20);
	setfillstyle(SOLID_FILL, color2);
	bar(x1, y1, x2, y2);
	return 0;
}

int Win::exit()
{
	putimage(x1, y1, imagebuff, COPY_PUT);
	free(imagebuff);
	return 0;
}
