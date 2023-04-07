#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include <dos.h>
#include "printg.h"
//开始界面
int page5()
{
	int nx , ny, nb, temp, part = 1;
	int mousig[10] = {0};
	int nylist[10] = {0};
	float ar1 = 0, br1 = 0; //example
	float signal1;
	bar2d(0, 0, 639, 479, LIGHTGRAY);
	bar3d(0, 33, 120, 480, LIGHTGRAY, 0);
	
	bar3d(0, 0, 639, 32, LIGHTGRAY, 0);
	bar3d(1, 0, 80, 30, LIGHTGRAY, 0);
	bar3d(81, 0, 160, 30, LIGHTGRAY, 0);
	bar3d(161, 0, 240, 30, LIGHTGRAY, 0);
	bar3d(241, 0, 320, 30, LIGHTGRAY, 0);
	bar2d(2, 440, 118, 477, RED);
	//button(0, 23, 98, 63, 0);
	//button(0, 64, 98, 104, 0);
	//button(0, 105, 98, 145, 0);
	//button(442, 24, 472, 54, 0);
	button(2, 440, 118, 477, 0);
	clrmous(ny, nx);
	printg(200, 200, BLACK, "AAAAaaaa");
	rectangle(200, 200, 207, 207);
	while(1)
	{
		/*
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
		*/
		if(mouse_press(2, 440, 118, 477) == 1)
		{
			button(2, 440, 118, 477, 1);
			return 0;
		}
		//refresh area
		/*
		else if(mouse_press(0, 0, 150, 200) == 2)
		{
			button(0, 23, 98, 63, mousig[0]);
			button(0, 64, 98, 104, mousig[1]);
			button(0, 105, 98, 145, mousig[2]);
		}
		*/
		newmouse(&nx, &ny, &nb);
		if(temp > 0)
		{
			nylist[0] = temp;
		}
		delay(20);
	}
	return 0;
}