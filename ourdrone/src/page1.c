#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include "onoff.h"
#include "printg.h"
#include "page234.h"
//菜单�?
int page1()
{
	int nx , ny, nb, temp, part = 1;
	int mousig[10] = {0};
	int nylist[10] = {0};
	float ar1 = 0, br1 = 0; //example
	float signal1;
	bar2d(0, 0, 639, 479, LIGHTGRAY);
	bar3d(0, 0, 100, 480, LIGHTGRAY, 0);
	bar3d(100, 0, 639, 20, LIGHTGRAY, 0);
	bar3d(440, 21, 639, 479, DARKGRAY, 1);
	bar2d(442, 24, 637, 200, BLACK);
	bar2d(442, 24, 472, 54, BLUE);
	bar2d(2, 440, 98, 477, RED);
	button(0, 23, 98, 63, 0);
	button(0, 64, 98, 104, 0);
	button(0, 105, 98, 145, 0);
	button(442, 24, 472, 54, 0);
	button(2, 440, 98, 477, 0);
	sliderbase(617, 201, nx, ny, 20, 278, 0, 0, 0);
	clrmous(ny, nx);
	while(1)
	{
		if(mouse_press(0, 23, 98, 63) == 1)
		{
			button(0, 23, 98, 63, 1);
			part = 1;
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130, 40, 180, 60);
		}
		else if(mouse_press(0, 64, 98, 104) == 1)
		{
			button(0, 64, 98, 104, 1);
			part = 2;
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130, 40, 180, 60);
		}
		else if(mouse_press(0, 105, 98, 145) == 1)
		{
			button(0, 105, 98, 145, 1);
			part = 3;
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130, 40, 180, 60);
		}
		else if(mouse_press(2, 440, 98, 477) == 1)
		{
			button(2, 440, 98, 477, 1);
			return 0;
		}
		
		newmouse(&nx, &ny, &nb);
		temp = slider(617, 201, nx, ny, 20, 278, 0, 0, &signal1);
//switch part
		switch(part)
		{
			case 1:
			bar2d(442, 55, 637, 200, BLACK);
			example(ar1, br1, 540, 110, 20, 10, 1);
			printg(130, 40, 0, "part %d", part);
			if(mouse_press(442, 24, 472, 54) == 1)
			{
				button(442, 24, 472, 54, 1);
				return 2;
			}
			ar1 += 0.05;
			br1 += 0.05;
			break;
			case 2:
			bar2d(442, 55, 637, 200, BLACK);
			printg(130, 40, 0, "part %d", part);
			if(mouse_press(442, 24, 472, 54) == 1)
			{
				button(442, 24, 472, 54, mousig[3]);
				return 3;
			}
			break;
			case 3:
			bar2d(442, 55, 637, 200, BLACK);
			printg(130, 40, 0, "part %d", part);
			if(mouse_press(442, 24, 472, 54) == 1)
			{
				button(442, 24, 472, 54, mousig[3]);
				return 4;
			}
			break;
		}
		if(temp > 0)
		{
			nylist[0] = temp;
		}
		newmouse(&nx, &ny, &nb);
		delay(20);
	}
	return 0;
}