#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include <dos.h>
#include "printg.h"
#include "hz.h"
#include "cla.h"
#include "win.h"
//ͼ�λ����?

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
	A B;
	Win win1(100, 100, 300, 250, BLACK, DARKGRAY);
	delay(500);
	win1.update(200, 200, 400, 350, GREEN, LIGHTGREEN);
	delay(500);
	win1.exit();
	printg_cn(100, 100, 0, style, "qwer%z", "ιιι");
	//setcolor(BLACK);
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