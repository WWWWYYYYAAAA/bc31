#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include <dos.h>
#include "printg.h"
#include "hz.h"
//#include "win.h"
#include "onoff.h"

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
	int nx, ny, nb, x1 = 100, y1 = 100, x2 = 300, y2 = 250;
	int x21 = 300, y21 = 300, x22 = 400, y22 = 400;
	int style[5] = {0, 2, 0, 0, 1};
	mouseinit();
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(0, 0, 639, 479);
	bar3d(180, 300, 460, 360, DARKGRAY, 0);
	button(180, 300, 460, 360, 0);
	bar3d(180, 380, 460, 440, DARKGRAY, 0);
	button(180, 380, 460, 440, 0);
	printg(300, 220, 0, "title");
	//A B;
	//Win win1(x1, y1, x2, y2, BLACK, DARKGRAY), win2(x21, y21, x22, y22, BLACK, DARKGRAY);
	//win1.update(x1+=100, y1+=100, x2+=100, y2+=100, GREEN, LIGHTGREEN);
	//win2.update(x21+=100, y21+=100, x22+=100, y22+=100, GREEN, LIGHTGREEN);
	//delay(500);
	//win1.exit();
	//printg_cn(100, 100, 0, style, "qwer%z", "ιιι");
	style[4] = 4;
	//printg_cn(200, 200, 0, style, "qwer%z", "ιιι");
	//setcolor(BLACK);
	//rectangle(100, 190, 139, 237);
	newmouse(&nx, &ny, &nb);
	Mouse_move cotrolm(nx, ny);
	while(1)
	{
		newmouse(&nx, &ny, &nb);
		//cotrolm.update(nx, ny);
		//win1.update(x1+=cotrolm.dx, y1+=cotrolm.dy, x2+=cotrolm.dx, y2+=cotrolm.dy, GREEN, LIGHTGREEN);
		if(mouse_press(180, 300, 460, 360) == 1)
		{
			button(180, 300, 460, 360, 1);
			//win1.exit();
			return 1;
		}
		if(mouse_press(180, 380, 460, 440) == 1)
		{
			button(180, 380, 460, 440, 1);
		   //	win1.exit();
			return 5;
		}
		delay(30);
	}
	return 0;
}