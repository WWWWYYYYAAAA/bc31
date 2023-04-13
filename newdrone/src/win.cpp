#include <graphics.h>
#include <alloc.h>
#include "win.h"
#include "mouse.h"
#include "visual.h"

Win::Win(int ix1, int iy1, int ix2, int iy2, int icolor1, int icolor2)
{
	int nx, ny, nb;
	mread(&nx, &ny, &nb);
	enable = 0;
	count = 0;
	x1 = ix1;
	y1 = iy1;
	x2 = ix2;
	y2 = iy2;
	lx = nx;
	ly = ny;
	imsize = imagesize(x1, y1, x2+20, y2+20);
	imagebuff = (void far *) farmalloc(imsize);
	getimage(x1, y1, x2+20, y2+20, imagebuff);
	color1 = icolor1;
	color2 = icolor2;
	setfillstyle(SOLID_FILL, color1);
	bar(x1+20, y1+20, x2+20, y2+20);
	setfillstyle(SOLID_FILL, color2);
	bar3d(x1, y1, x2, y1+20, LIGHTGRAY, 0);
	bar(x1, y1, x2, y2);
}

int Win::update(int ix1, int iy1, int ix2, int iy2, int icolor1, int icolor2)
{
	int nx, ny, nb;
	mread(&nx, &ny, &nb);
	putimage(x1, y1, imagebuff, COPY_PUT);
	x1 = ix1>0?ix1:0;
	y1 = iy1>0?iy1:0;
	x2 = ix2<620?ix2:619;
	y2 = iy2<460?iy2:459;
	lx = nx;
	ly = ny;
	color1 = icolor1;
	color2 = icolor2;
	getimage(x1, y1, x2+20, y2+20, imagebuff);
	setfillstyle(SOLID_FILL, color1);
	bar(x1+20, y1+20, x2+20, y2+20);
	setfillstyle(SOLID_FILL, color2);
	bar(x1, y1, x2, y2);
	bar3d(x1, y1, x2, y1+20, LIGHTGRAY, 0);
	return 0;
}

int Win::exit()
{
	putimage(x1, y1, imagebuff, COPY_PUT);
	free(imagebuff);
	return 0;
}

int Win::clearwin()
{
	putimage(x1, y1, imagebuff, COPY_PUT);
	return 0;
}

int Win::auto_update()
{
	int nx, ny, nb;
	mread(&nx, &ny, &nb);
	if(mouse_press(x1, y1, x2, y1+20) == 1)
	{
		enable = 1;
	}
	else
	{
		enable = 0;
	}
	if(enable)
	{
		update(x1 + nx - lx, y1 + ny - ly, x2 + nx - lx, y2 + ny - ly, color1, color2);
		return 1;
	}
	else
	{
		if((count >> 4) == 1)
		{
			//update(x1, y1, x2, y2, color1, color2);
			bar3d(x1, y1, x2, y1+20, LIGHTGRAY, 0);
			count = 0;
			return 1;
		}
		count ++;
	}
	lx = nx;
	ly = ny;
	return 0;
}
