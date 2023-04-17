#include <graphics.h>
#include <dos.h>
#include "printg.h"
#include "visual.h"
#include "mouse.h"
extern int MX, MY;

void ball(int x, int y, int r, int color)
{
	setwritemode(COPY_PUT);
	//setcolor(color);
	setfillstyle(SOLID_FILL, color);
	//circle(x, y, r);
	//floodfill(x, y, color);
	//setcolor(DARKGRAY);
	//circle(x, y, r+2);
	//floodfill(x, y, DARKGRAY);
	fillellipse(x, y, r, r);
	setwritemode(XOR_PUT);
	setcolor(color);
	circle(x, y, r);
	setwritemode(COPY_PUT);
}

void bar3d(int x1, int y1, int x2, int y2, int color, int style)
{
	switch(style)
	{
		case 0:
			setwritemode(COPY_PUT);
			setcolor(color);
			setfillstyle(SOLID_FILL, color);
			setcolor(WHITE);
			bar(x1, y1, x2, y2);
			line(x1, y1, x2, y1);
			line(x1, y1+1, x2-1, y1+1);
			line(x1, y1, x1, y2);
			line(x1+1, y1, x1+1, y2-1);
			setcolor(BLACK);
			line(x1+1, y2, x2, y2);
			line(x1+2, y2-1, x2, y2-1);
			line(x2, y1+1, x2, y2);
			line(x2-1, y1+2, x2-1, y2);
			break;
		case 1:
			setwritemode(COPY_PUT);
			setcolor(color);
			setfillstyle(SOLID_FILL, color);
			bar(x1, y1, x2, y2);
			setwritemode(COPY_PUT);
			setcolor(BLACK);
			line(x1, y1, x2, y1);
			line(x1, y1+1, x2-1, y1+1);
			line(x1, y1, x1, y2);
			line(x1+1, y1, x1+1, y2-1);
			setcolor(WHITE);
			line(x1+1, y2, x2, y2);
			line(x1+2, y2-1, x2, y2-1);
			line(x2, y1+1, x2, y2);
			line(x2-1, y1+2, x2-1, y2);
			break;
	}
}

int button(int x1, int y1, int x2, int y2, int state)
{
	switch(state)
	{
		case 1:
			clrmous(MX, MY);
			setwritemode(COPY_PUT);
			setcolor(0);
			line(x1, y1, x2, y1);
			line(x1, y1+1, x2-1, y1+1);
			line(x1, y1, x1, y2);
			line(x1+1, y1, x1+1, y2-1);
			setcolor(15);
			line(x1+1, y2, x2, y2);
			line(x1+2, y2-1, x2, y2-1);
			line(x2, y1+1, x2, y2);
			line(x2-1, y1+2, x2-1, y2);
			delay(50);
		case 0:
			setwritemode(COPY_PUT);
			setcolor(15);
			line(x1, y1, x2, y1);
			line(x1, y1+1, x2-1, y1+1);
			line(x1, y1, x1, y2);
			line(x1+1, y1, x1+1, y2-1);
			setcolor(0);
			line(x1+1, y2, x2, y2);
			line(x1+2, y2-1, x2, y2-1);
			line(x2, y1+1, x2, y2);
			line(x2-1, y1+2, x2-1, y2);
			break;
		case 2:
			clrmous(MX, MY);
			setwritemode(COPY_PUT);
			setcolor(0);
			line(x1, y1, x2, y1);
			line(x1, y1+1, x2-1, y1+1);
			line(x1, y1, x1, y2);
			line(x1+1, y1, x1+1, y2-1);
			setcolor(15);
			line(x1+1, y2, x2, y2);
			line(x1+2, y2-1, x2, y2-1);
			line(x2, y1+1, x2, y2);
			line(x2-1, y1+2, x2-1, y2);
		break;
	}
	return state;
}

void bar2d(int x1, int y1, int x2, int y2, int color)
{
	setwritemode(COPY_PUT);
	setfillstyle(SOLID_FILL, color);
	bar(x1, y1, x2, y2);
}

void sliderbase(int x0, int y0, int nx, int ny, int wid, int len, int direct, int style, int mode)
{
	switch(mode)
	{
	case 0:
		switch(style)
		{
		case 0:
			bar2d(x0, y0, x0+wid, y0+len, LIGHTGRAY);
			bar3d(x0+2, y0+2, x0+wid-2, y0+22, DARKGRAY, 0);
		break;
		}
	break;
	case 1:
		switch(style)
		{
		case 0:
			if(ny < y0)
				ny = y0;
			else if(ny > y0+len-20)
				ny = y0 +len-20;
			bar2d(x0, y0, x0+wid, y0+len, LIGHTGRAY);
			bar3d(x0+2, ny+2, x0+wid-2, ny+22, DARKGRAY, 0);
		break;
		}
	break;
	}
}

int slider(int x0, int y0, int nx, int ny, int wid, int len, int direct, int style, float *signal)
{
	switch(style)
	{
	case 0:
		if(mouse_press(x0-20, y0, x0+wid, y0+len) == 1)
		{
			clrmous(MX, MY);
			*signal = 100.0 * (ny - y0) / len;
			sliderbase(x0, y0, nx, ny, wid, len, direct, style, 1);
			return ny;
		}
		break;
	}
	ny = -1;
	return ny;
}

//在更新鼠标后该函数弃用
void silder_depature(int nynum, int x0, int y0, int wid, int len, int direct, int style)
{
		if(mouse_press(x0-20, y0, x0+wid+20, y0+len) == 2)
		{
			sliderbase(x0, y0, 0, nynum, wid, len, direct, style, 1);
		}
}