#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include <dos.h>
#include "printg.h"
#include "hz.h"
//#include "windows.h"
//图形化输出

class  Windows
{
public:
	int x1;
	int y1;
	int x2;
	int y2;
	int color1;
	int color2;
	
	Windows(int ix1, int iy1, int ix2, int iy2, int icolor1, int icolor2);
};

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



int initialization()
{
	int i;
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, 0, 639, 479);
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(WHITE);
	rectangle(160, 300, 480, 320);
	printg(160, 285, 15, "Initializing...");
	for(i=0; i<100; i++)
	{
		setfillstyle(SOLID_FILL, WHITE);
		bar(160, 300, 3.2*i+161, 320);
		delay(1);
	}
	return 0;
}

int page0()
{
	int nx, ny, nb;
	int style[5] = {0, 2, 0, 0, 1};
	mouseinit();
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(0, 0, 639, 479);
	bar3d(180, 300, 460, 360, DARKGRAY, 0);
	button(180, 300, 460, 360, 0);
	bar3d(180, 380, 460, 440, DARKGRAY, 0);
	button(180, 380, 460, 440, 0);
	printg(300, 220, 0, "title");
	Windows win1(100, 100, 300, 250, BLACK, DARKGRAY);
	/*
	puthz(100, 100, 16, 26, BLACK, "无人机");
	puthz(100, 120, 24, 34, BLACK, "无人机");
	puthz(100, 150, 32, 42, BLACK, "无人机");
	puthz(100, 190, 48, 58, BLACK, "无机人");
	*/
	printg_cn(100, 100, 0, style, "qwer%z", "威威");
	setcolor(BLACK);
	//rectangle(100, 190, 139, 237);
	while(1)
	{
		newmouse(&nx, &ny, &nb);
		if(mouse_press(180, 300, 460, 360) == 1)
		{
			button(180, 300, 460, 360, 1);
			return 1;
		}
		if(mouse_press(180, 380, 460, 440) == 1)
		{
			button(180, 380, 460, 440, 1);
			return 5;
		}
	}
	return 0;
}